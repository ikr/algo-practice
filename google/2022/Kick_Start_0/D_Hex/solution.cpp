#include <cassert>
#include <functional>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
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

optional<vector<RoCo>>
connection_path(const vector<string> &grid, const RoCo source,
                const function<bool(RoCo)> is_destination,
                const set<RoCo> &used) {
    assert(grid[source.first][source.second] != '.');
    vector<vector<bool>> visited(sz(grid), vector(sz(grid[0]), false));
    vector<vector<RoCo>> anc(sz(grid), vector(sz(grid[0]), RoCo{-1, -1}));

    const auto dfs = [&](const auto &self, const RoCo u) -> optional<RoCo> {
        const auto [ro, co] = u;
        visited[ro][co] = true;
        if (is_destination(u) && !used.count(u)) return u;

        for (const auto v : adjacent_hexagons_of_same_color(grid, u)) {
            const auto [ro_, co_] = v;
            if (visited[ro_][co_] || used.count(v)) continue;

            anc[ro_][co_] = u;
            const auto sub = self(self, v);
            if (sub) return sub;
        }

        return nullopt;
    };

    const auto dest = dfs(dfs, source);

    if (dest) {
        vector<RoCo> result;

        auto curr = *dest;
        while (curr != RoCo{-1, -1}) {
            result.push_back(curr);
            curr = anc[curr.first][curr.second];
        }

        reverse(begin(result), end(result));
        // cerr << result << endl;
        return result;
    }

    return nullopt;
}

int connections_num(const vector<string> &grid, const vector<RoCo> sources,
                    const function<bool(RoCo)> is_destination) {
    int result{};
    set<RoCo> used;

    for (const auto u : sources) {
        const auto path = connection_path(grid, u, is_destination, used);
        if (path) {
            ++result;
            used.insert(cbegin(*path), cend(*path));
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

enum class PlayerPosition { NEUTRAL, IMPOSSIBLE, POTENTIAL_WIN };

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

        // const auto bcs = connections_num(grid, blue_sources(grid),
        //                                  make_is_blue_destiation(sz(grid)));
        // cerr << "BCS:" << bcs << endl;

        cout << "Case #" << i << ": " << outcome_literal(solve(grid)) << '\n';
    }

    return 0;
}
