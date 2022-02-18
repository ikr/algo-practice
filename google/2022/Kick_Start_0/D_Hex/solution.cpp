#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
#include <vector>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

using RoCo = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

enum class Outcome { IMPOSSIBLE, BLUE_WINS, RED_WINS, NEUTRAL };

string outcome_literal(const Outcome x) {
    switch (x) {
    case Outcome::IMPOSSIBLE:
        return "Impossible";
    case Outcome::BLUE_WINS:
        return "Blue wins";
    case Outcome::RED_WINS:
        return "Red wins";
    case Outcome::NEUTRAL:
    default:
        return "Nobody wins";
    }
}

constexpr bool in_bounds(const int N, const RoCo roco) {
    const auto [ro, co] = roco;
    return 0 <= ro && ro < N && 0 <= co && co < N;
}

static const vector<RoCo> HEXAGON_DELTAS{{-1, 0}, {-1, 1}, {0, 1},
                                         {1, 0},  {1, -1}, {0, -1}};

vector<RoCo> adjacent_hexagons_of_same_color(const vector<string> &grid,
                                             const RoCo roco) {
    const auto [ro, co] = roco;
    const auto color = grid[ro][co];
    assert(color == 'B' || color == 'R');
    vector<RoCo> result;

    for (const auto d : HEXAGON_DELTAS) {
        const auto roco_ = roco + d;
        if (!in_bounds(sz(grid), roco_)) continue;

        const auto [ro_, co_] = roco_;
        if (grid[ro_][co_] != color) continue;

        result.emplace_back(ro_, co_);
    }

    return result;
}

vector<RoCo> blue_sources(const vector<string> &grid) {
    vector<RoCo> result;
    for (int ro = 0; ro < sz(grid); ++ro) {
        if (grid[ro][0] == 'B') {
            result.emplace_back(ro, 0);
        }
    }
    return result;
}

vector<RoCo> red_sources(const vector<string> &grid) {
    vector<RoCo> result;
    for (int co = 0; co < sz(grid[0]); ++co) {
        if (grid[0][co] == 'R') {
            result.emplace_back(0, co);
        }
    }
    return result;
}

function<bool(RoCo)> make_is_blue_source(const int N) {
    return [N](const RoCo roco) -> bool {
        const auto [_, co] = roco;
        return co == 0;
    };
}

function<bool(RoCo)> make_is_blue_destiation(const int N) {
    return [N](const RoCo roco) -> bool {
        const auto [_, co] = roco;
        return co == N - 1;
    };
}

function<bool(RoCo)> make_is_red_source(const int N) {
    return [N](const RoCo roco) -> bool {
        const auto [ro, _] = roco;
        return ro == 0;
    };
}

function<bool(RoCo)> make_is_red_destiation(const int N) {
    return [N](const RoCo roco) -> bool {
        const auto [ro, _] = roco;
        return ro == N - 1;
    };
}

pair<int, int> blue_red_num(const vector<string> &grid) {
    int bs{};
    int rs{};

    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[0]); ++co) {
            switch (grid[ro][co]) {
            case 'B':
                ++bs;
                break;
            case 'R':
                ++rs;
                break;
            }
        }
    }

    return {bs, rs};
}

enum class PlayerPosition { NEUTRAL, IMPOSSIBLE, POTENTIAL_WIN };

bool is_bridging_source(const vector<string> &grid, const RoCo source,
                        const function<bool(RoCo)> is_destination) {
    vector<vector<bool>> visited(sz(grid), vector(sz(grid[0]), false));

    const auto dfs = [&](const auto &self, const RoCo u) -> bool {
        if (is_destination(u)) return true;
        const auto [ro, co] = u;
        visited[ro][co] = true;

        for (const auto v : adjacent_hexagons_of_same_color(grid, u)) {
            if (visited[v.first][v.second]) continue;
            if (self(self, v)) return true;
        }

        return false;
    };

    return dfs(dfs, source);
}

set<RoCo> component_of(const vector<string> &grid, const vector<RoCo> rocos,
                       const optional<RoCo> punctured) {
    set<RoCo> result;

    const auto dfs = [&](const auto &self, const RoCo u) -> void {
        result.insert(u);
        for (const auto v : adjacent_hexagons_of_same_color(grid, u)) {
            if (result.count(v) || (punctured && *punctured == v)) continue;
            self(self, v);
        }
    };

    for (const auto roco : rocos) {
        if (punctured) {
            assert(*punctured != roco);
        }
        dfs(dfs, roco);
    }
    return result;
}

bool is_1_connected(const vector<string> &grid, const set<RoCo> &component,
                    const function<bool(RoCo)> is_source,
                    const function<bool(RoCo)> is_destination) {
    vector<RoCo> component_sources;
    copy_if(cbegin(component), cend(component),
            back_inserter(component_sources), is_source);
    assert(!component_sources.empty());

    for (const auto punctured : component) {
        if (is_source(punctured) || is_destination(punctured)) {
            continue;
        }
        const auto c = component_of(grid, component_sources, punctured);
        if (none_of(cbegin(c), cend(c), is_destination)) {
            // cerr << "src: " << src
            //      << " key stone: " << punctured << endl;
            return true;
        }
    }

    return false;
}

PlayerPosition
evaluate_standalone_player_position(const vector<string> &grid,
                                    const vector<RoCo> &sources,
                                    const function<bool(RoCo)> is_source,
                                    const function<bool(RoCo)> is_destination) {
    const auto b_src_it =
        find_if(cbegin(sources), cend(sources), [&](const auto src) {
            return is_bridging_source(grid, src, is_destination);
        });

    if (b_src_it == cend(sources)) return PlayerPosition::NEUTRAL;

    const auto bridge = component_of(grid, {*b_src_it}, nullopt);

    for (auto it = next(b_src_it); it != cend(sources); ++it) {
        if (bridge.count(*it)) continue;

        if (is_bridging_source(grid, *it, is_destination)) {
            return PlayerPosition::IMPOSSIBLE;
        }
    }

    if (count_if(cbegin(bridge), cend(bridge), is_source) == 1 ||
        count_if(cbegin(bridge), cend(bridge), is_destination) == 1) {
        return PlayerPosition::POTENTIAL_WIN;
    }

    return is_1_connected(grid, bridge, is_source, is_destination)
               ? PlayerPosition::POTENTIAL_WIN
               : PlayerPosition::IMPOSSIBLE;
}

Outcome solve(const vector<string> &grid) {
    const auto N = sz(grid);
    const auto [bs, rs] = blue_red_num(grid);
    if (abs(bs - rs) > 1) return Outcome::IMPOSSIBLE;

    const auto position_of_blue = evaluate_standalone_player_position(
        grid, blue_sources(grid), make_is_blue_source(N),
        make_is_blue_destiation(N));

    if (position_of_blue == PlayerPosition::IMPOSSIBLE) {
        return Outcome::IMPOSSIBLE;
    }

    const auto position_of_red = evaluate_standalone_player_position(
        grid, red_sources(grid), make_is_red_source(N),
        make_is_red_destiation(N));

    if (position_of_red == PlayerPosition::IMPOSSIBLE) {
        return Outcome::IMPOSSIBLE;
    }

    if (position_of_blue == PlayerPosition::NEUTRAL &&
        position_of_red == PlayerPosition::NEUTRAL) {
        assert(bs + rs < N * N);
        return Outcome::NEUTRAL;
    }

    if (position_of_blue == PlayerPosition::POTENTIAL_WIN) {
        assert(position_of_red == PlayerPosition::NEUTRAL);
        return rs > bs ? Outcome::IMPOSSIBLE : Outcome::BLUE_WINS;
    } else {
        assert(position_of_red == PlayerPosition::POTENTIAL_WIN);
        assert(position_of_blue == PlayerPosition::NEUTRAL);
        return bs > rs ? Outcome::IMPOSSIBLE : Outcome::RED_WINS;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<string> grid(N);
        for (auto &row : grid) {
            cin >> row;
        }

        cout << "Case #" << i << ": " << outcome_literal(solve(grid)) << '\n';
    }

    return 0;
}
