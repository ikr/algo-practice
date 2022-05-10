#include <array>
#include <iostream>
#include <string>
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
        string xs;
        cin >> xs;

        array<int, 6> ys{};
        for (int i = 0; i < sz(xs); ++i) {
            ys[i] = inof(xs[i]) - inof('0');
        }

        const bool ans = (ys[0] + ys[1] + ys[2]) == (ys[3] + ys[4] + ys[5]);
        cout << (ans ? "YES" : "NO") << '\n';
    }

    return 0;
}
