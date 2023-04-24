#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int q;
    cin >> q;
    while (q--) {
        int n, t;
        cin >> n >> t;

        vector<int> A(n);
        for (auto &a : A) cin >> a;

        vector<int> B(n);
        for (auto &b : B) cin >> b;

        int ans = -1;
        int hi = 0;

        for (int i = 0; i < n; ++i) {
            const auto t_left = t - i;
            if (t_left >= A[i] && B[i] > hi) {
                ans = i + 1;
                hi = B[i];
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
