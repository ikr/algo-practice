#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using Tri = pair<int, pii>;

static constexpr int INF = 1e9;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

int min_total_risk_dijkstra(const vvi &grid) {
    const int H = sz(grid);
    const int W = sz(grid[0]);

    const auto in_bounds = [&](const pii roco) -> bool {
        const auto [ro, co] = roco;
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    vvi D(H, vi(W, INF));
    D[0][0] = 0;

    set<Tri> q;
    q.emplace(0, pii{0, 0});

    while (!q.empty()) {
        const auto v = cbegin(q)->second;
        q.erase(cbegin(q));

        const auto [ro, co] = v;

        for (const auto delta : vector<pii>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
            const auto [ro_, co_] = v + delta;
            if (!in_bounds({ro_, co_})) continue;

            if (D[ro][co] + grid[ro_][co_] < D[ro_][co_]) {
                q.erase(Tri{D[ro_][co_], {ro_, co_}});
                D[ro_][co_] = D[ro][co] + grid[ro_][co_];
                q.emplace(D[ro_][co_], pii{ro_, co_});
            }
        }
    }

    return D.back().back();
}

int main() {
    vector<string> lines;

    for (string line; getline(cin, line);) {
        lines.push_back(line);
    }

    const int H = sz(lines);
    const int W = sz(lines[0]);

    vvi grid(H, vi(W, -1));
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            grid[ro][co] = inof(lines[ro][co]) - inof('0');
        }
    }

    vvi mega_grid(5 * H, vi(5 * W, -1));
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            const auto local_val = [&](const int x) -> int {
                if (i + j == 0) return x;
                const int a = i + j;
                return ((x - 1 + a) % 9) + 1;
            };

            for (int ro = 0; ro < H; ++ro) {
                for (int co = 0; co < W; ++co) {
                    mega_grid[i * H + ro][j * W + co] = local_val(grid[ro][co]);
                }
            }
        }
    }

    cout << min_total_risk_dijkstra(mega_grid) << '\n';
    return 0;
}
