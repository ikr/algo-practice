#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_ops(const vector<string> &G) {
    const auto n = sz(G);
    vector<vector<int>> D(n, vector(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < sz(G[i]); ++j) {
            D[i][j] = G[i][j] - 'a';
        }
    }

    const auto fix_first = [&]() -> int {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < sz(G[i]); ++j) {
                const auto x = D[i][j];
                const auto y = D[n - 1 - i][j];
                if (x == y) continue;

                const auto d = abs(x - y);

                if (x < y) {
                    D[i][j] += d;
                    return d;
                } else {
                    D[n - 1 - i][j] += d;
                    return d;
                }
            }
        }

        return 0;
    };

    int ans{};

    for (;;) {
        const auto d = fix_first();
        if (d == 0) break;
        ans += d;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<string> G(n);
        for (auto &row : G) cin >> row;

        cout << min_ops(G) << '\n';
    }

    return 0;
}
