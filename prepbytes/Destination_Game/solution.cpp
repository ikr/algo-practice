#include <cassert>
#include <iostream>
#include <utility>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

using ll = long long;

bool is_possible(const ll x, const ll y) {
    assert(x <= y);
    if (x == 1) return true;
    if (x < 1) return false;

    const auto k = y / x;
    const auto y_ = y - k * x;
    return is_possible(min(x, y_), max(x, y_));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll x, y;
        cin >> x >> y;
        if (x > y) swap(x, y);

        cout << (is_possible(x, y) ? "Yes" : "No") << '\n';
    }

    return 0;
}
