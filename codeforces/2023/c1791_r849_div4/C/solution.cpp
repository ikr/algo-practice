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
        int n;
        cin >> n;

        string xs;
        cin >> xs;

        assert(sz(xs) == n);

        int ans = n;
        for (int i = 0, j = n - 1; i < j; ++i, --j) {
            if (xs[i] == xs[j]) {
                break;
            } else {
                ans -= 2;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
