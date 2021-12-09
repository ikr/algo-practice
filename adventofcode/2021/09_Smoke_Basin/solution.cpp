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

vector<pii> all_valleys(const vvi &grid) {
    const int H = sz(grid);
    const int W = sz(grid[0]);
    vector<pii> ans;

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
                ans.emplace_back(ro, co);
            }
        }
    }

    return ans;
}

int basin_size(const vvi &grid, const pii src) {
    const int H = sz(grid);
    const int W = sz(grid[0]);
    set<pii> visited{{src}};

    function<void(pii)> recur;
    recur = [&](const pii u) {
        const auto [ro, co] = u;

        for (const auto [da, db] :
             vector<pii>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
            const auto [a, b] = pii{ro, co} + pii{da, db};
            if (0 <= a && a < H && 0 <= b && b < W &&
                !visited.count(pii{a, b}) && grid[a][b] != 9) {
                visited.emplace(a, b);
                recur({a, b});
            }
        }
    };

    recur(src);
    return sz(visited);
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

int main() {
    vvi grid;

    for (string line; getline(cin, line);) {
        vi xs;

        for (const char c : line) {
            const auto x = inof(c) - inof('0');
            xs.push_back(x);
        }

        grid.push_back(xs);
    }

    const auto valleys = all_valleys(grid);
    vi bss(sz(valleys));
    transform(cbegin(valleys), cend(valleys), begin(bss),
              [&](const pii ab) { return basin_size(grid, ab); });
    sort(rbegin(bss), rend(bss));

    const ll ans = llof(bss[0]) * bss[1] * bss[2];
    cout << ans << '\n';
    return 0;
}
