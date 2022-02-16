#include <cassert>
#include <functional>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

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

static const vector<RoCo> HEXAGON_DELTAS{{-1, 0}, {1, -1}, {0, 1},
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

optional<RoCo> connection_destination(const vector<string> &grid,
                                      const RoCo source,
                                      const function<bool(RoCo)> is_destination,
                                      const set<RoCo> &used_destinations) {
    assert(grid[source.first][source.second] != '.');
    vector<vector<bool>> visited(sz(grid), vector(sz(grid[0]), false));

    const auto dfs = [&](const auto &self, const RoCo u) -> optional<RoCo> {
        const auto [ro, co] = u;
        visited[ro][co] = true;
        if (is_destination(u) && !used_destinations.count(u)) return u;

        for (const auto v : adjacent_hexagons_of_same_color(grid, u)) {
            const auto [ro_, co_] = v;
            if (visited[ro_][co_]) continue;

            const auto sub = self(self, v);
            if (sub) return sub;
        }

        return nullopt;
    };

    return dfs(dfs, source);
}

int connections_num(const vector<string> &grid, const vector<RoCo> sources,
                    const function<bool(RoCo)> is_destination) {
    int result{};
    set<RoCo> used_destinations;

    for (const auto u : sources) {
        const auto dest =
            connection_destination(grid, u, is_destination, used_destinations);
        if (dest) {
            ++result;
            used_destinations.insert(*dest);
        }
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

function<bool(RoCo)> make_is_blue_destiation(const int N) {
    return [N](const RoCo roco) -> bool {
        const auto [_, co] = roco;
        return co == N - 1;
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

Outcome solve(const vector<string> &grid) {
    const auto [bs, rs] = blue_red_num(grid);
    if (abs(bs - rs) > 1) return Outcome::IMPOSSIBLE;

    const auto bcs = connections_num(grid, blue_sources(grid),
                                     make_is_blue_destiation(sz(grid)));
    if (bcs > 1) return Outcome::IMPOSSIBLE;

    const auto rcs = connections_num(grid, red_sources(grid),
                                     make_is_red_destiation(sz(grid)));
    if (rcs > 1) return Outcome::IMPOSSIBLE;
    if (bcs && rcs) return Outcome::IMPOSSIBLE;

    if (!bcs && !rcs) return Outcome::NEUTRAL;

    if (bcs) {
        return rs > bs ? Outcome::IMPOSSIBLE : Outcome::BLUE_WINS;
    } else {
        assert(rcs);
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
