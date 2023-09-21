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
        string xs;
        cin >> xs;

        const auto yes = [&]() -> bool {
            if (xs == "abc") return true;

            {
                auto ys = xs;
                swap(ys[0], ys[1]);
                if (ys == "abc") return true;
            }
            {
                auto ys = xs;
                swap(ys[1], ys[2]);
                if (ys == "abc") return true;
            }
            {
                auto ys = xs;
                swap(ys[0], ys[2]);
                if (ys == "abc") return true;
            }

            return false;
        }();

        cout << (yes ? "YES\n" : "NO\n");
    }

    return 0;
}
