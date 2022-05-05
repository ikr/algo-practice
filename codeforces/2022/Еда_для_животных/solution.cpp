#include <iostream>
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
        int a, b, c, x, y;
        cin >> a >> b >> c >> x >> y;

        x -= min(x, a);
        y -= min(y, b);
        const bool yes = (x + y) <= c;
        cout << (yes ? "YES" : "NO") << '\n';
    }

    return 0;
}
