#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

vi all_valleys(const vvi &grid) {
    const int H = sz(grid);
    const int W = sz(grid[0]);
    vi ans;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            vector<pii> adj;

            for (const auto [da, db] :
                 vector<pii>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
                const auto [a, b] = pii{ro, co} + pii{da, db};
                if (0 <= a && a < H && 0 <= b && b < W) {
                    adj.emplace_back(a, b);
                }
            }

            if (all_of(cbegin(adj), cend(adj), [&](const auto ab) {
                    const auto [a, b] = ab;
                    return grid[a][b] > grid[ro][co];
                })) {
                ans.push_back(grid[ro][co]);
            }
        }
    }

    return ans;
}

int main() {
    int ans{};
    vvi grid;

    for (string line; getline(cin, line);) {
        vi xs;

        for (const char c : line) {
            const auto x = inof(c) - inof('0');
            xs.push_back(x);
        }

        grid.push_back(xs);
    }

    const auto ys = all_valleys(grid);
    ans += transform_reduce(cbegin(ys), cend(ys), 0, plus<int>{},
                            [](const int x) { return x + 1; });
    cout << ans << '\n';
    return 0;
}
