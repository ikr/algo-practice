#include <array>
#include <cassert>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>
using namespace std;

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

optional<array<ll, 4>> find_quad(const ll L, const ll R) {
    if (L % 2 == 0) {
        return array{L, L + 1, L + 2, L + 3};
    }

    if (L + 4 > R) return nullopt;
    return array{L + 1, L + 2, L + 3, L + 4};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll L, R;
        cin >> L >> R;

        const auto ans = find_quad(L, R);
        if (ans) {
            cout << *ans << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}
