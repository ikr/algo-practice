#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        map<int, vector<int>> idx;
        for (int i = 0; i < n; ++i) {
            idx[xs[i]].push_back(i);
        }

        for (int j = 1; j <= k; ++j) {
            int a, b;
            cin >> a >> b;

            const auto yes =
                idx.count(a) && idx.count(b) && idx[a][0] < idx[b].back();
            cout << (yes ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}
