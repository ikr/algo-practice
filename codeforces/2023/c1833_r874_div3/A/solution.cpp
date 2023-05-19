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

        set<string> ms;
        for (int i = 1; i < n; ++i) {
            const string cur{xs[i - 1], xs[i]};
            ms.insert(cur);
        }

        cout << sz(ms) << '\n';
    }

    return 0;
}
