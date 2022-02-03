#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename T>
constexpr pair<T, T> times_k(const pair<T, T> a, const T k) {
    return {k * a.first, k * a.second};
}

using pii = pair<int, int>;
using tri = array<int, 3>;
using Graph = vector<vector<vector<tri>>>;

Graph build_graph(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    const auto in_bounds = [&](const pii roco) -> bool {
        const auto ro = roco.first;
        const auto co = roco.second;
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    Graph g(H, vector<vector<tri>>(W));

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            const auto roco = pii{ro, co};

            for (const auto delta :
                 vector<pii>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {

                for (int k = 1; in_bounds(roco + times_k(delta, k)); ++k) {
                    const auto t = roco + times_k(delta, k);
                    const auto ro_ = t.first;
                    const auto co_ = t.second;
                    if (grid[ro_][co_] == '#') continue;

                    if (k == 1) {
                        g[ro][co].push_back(tri{ro_, co_, 1});
                    } else {
                        const auto t_ = roco + times_k(delta, k + 1);
                        if (!in_bounds(t_)) continue;

                        const auto ro__ = t_.first;
                        const auto co__ = t_.second;
                        if (grid[ro__][co__] == '#') continue;
                        g[ro][co].push_back(tri{ro__, co__, 2});
                    }
                }
            }
        }
    }

    return g;
}

pair<pii, pii> find_endpoints(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    pii start{-1, -1};
    pii finish{-1, -1};

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == 'T') {
                start = pii{ro, co};
            } else if (grid[ro][co] == 'L') {
                finish = pii{ro, co};
            }
        }
    }

    return {start, finish};
}

static constexpr int INF = 1e8;

struct JumpingTiger final {
    int travel(const vector<string> &grid) const {
        const auto g = build_graph(grid);
        const auto endpoints = find_endpoints(grid);
        const auto start = endpoints.first;
        const auto finish = endpoints.second;

        vector<vector<int>> d(sz(grid), vector<int>(sz(grid[0]), INF));
        d[start.first][start.second] = 0;
        set<pair<int, pii>> q;
        q.emplace(0, start);

        while (!q.empty()) {
            const auto u = q.cbegin()->second;
            q.erase(q.cbegin());
            const auto d0 = d[u.first][u.second];

            for (const auto &v : g[u.first][u.second]) {
                const auto ro = v[0];
                const auto co = v[1];
                const auto w = v[2];

                if (d0 + w < d[ro][co]) {
                    q.erase({d[ro][co], pii{ro, co}});
                    d[ro][co] = d0 + w;
                    q.emplace(d0 + w, pii{ro, co});
                }
            }
        }

        return d[finish.first][finish.second] < INF
                   ? d[finish.first][finish.second]
                   : -1;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = JumpingTiger{}.travel({"T.######", "#..#####", "##..####", "###..###", "####..##", "#####..#", "######..", "#######L"});
        const auto expected = 14;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = JumpingTiger{}.travel({"T.######", "#..#####", "##..####", "###..###", "####..##", "#####..#", "######..", ".######L"});
        const auto expected = 14;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = JumpingTiger{}.travel({"T.######", "#..#####", "##..####", "###..###", "####..##", "#####..#", ".#####..", ".######L"});
        const auto expected = 6;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = JumpingTiger{}.travel({"T.######", "#..#####", "##..####", "###..###", "####..##", "#####..#", ".#####..", ".#####.L"});
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = JumpingTiger{}.travel({".##.", "#L##", "####", ".#T#"});
        const auto expected = -1;
        EXPECT(actual == expected);
    },
    CASE("Example 5") {
        const auto actual = JumpingTiger{}.travel({"T", "#", "#", "L", "#", "#", ".", "."});
        const auto expected = -1;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
