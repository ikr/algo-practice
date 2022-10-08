#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<vector<bool>> present(N + 1, vector(N + 1, false));

    for (int t = 1; t <= M; ++t) {
        int k;
        cin >> k;

        vector<int> xs(k);
        for (auto &x : xs) cin >> x;

        sort(begin(xs), end(xs));
        xs.erase(unique(begin(xs), end(xs)), end(xs));

        for (int i = 0; i < sz(xs) - 1; ++i) {
            for (int j = i + 1; j < sz(xs); ++j) {
                present[xs[i]][xs[j]] = true;
                present[xs[j]][xs[i]] = true;
            }
        }
    }

    bool ans = true;
    for (int i = 1; i <= N - 1; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (!present[i][j]) {
                ans = false;
                break;
            }
        }

        if (!ans) break;
    }

    cout << (ans ? "Yes" : "No") << '\n';
    return 0;
}
