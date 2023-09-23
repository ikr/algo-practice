#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    const auto yes = [&]() -> bool {
        for (int i = 1; i < sz(xs); ++i) {
            const auto a = xs[i - 1] - '0';
            const auto b = xs[i] - '0';
            if (a <= b) return false;
        }
        return true;
    }();

    cout << (yes ? "Yes\n" : "No\n");
    return 0;
}
