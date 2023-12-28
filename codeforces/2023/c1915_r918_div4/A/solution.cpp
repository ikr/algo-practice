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
        int a, b, c;
        cin >> a >> b >> c;

        if (a == b) {
            cout << c << '\n';
        } else if (b == c) {
            cout << a << '\n';
        } else {
            assert(a == c);
            cout << b << '\n';
        }
    }

    return 0;
}
