#include <algorithm>
#include <iostream>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_distance(const int a, const int b) {
    if (a == b) return 0;
    if (a == 1) return b;

    const auto g = __gcd(a, b);
    if (g == 1) return a + b;

    if (g == a) {
        if ((b / g) % a == 0) {
            return g + min_distance(min(a, b / g), max(a, b / g));
        }
        return b / a;
    }

    return a / g + b / g;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << min_distance(min(a, b), max(a, b)) << '\n';
    }

    return 0;
}
