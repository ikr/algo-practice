#include <algorithm>
#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_distance(const int a, const int b) {
    if (a == b) return 0;
    if (a % b == 0) return a / b;
    if (b % a == 0) return b / a;

    const auto g = __gcd(a, b);
    if (g == 1) return a + b;

    return min(a / g + min_distance(a / g, b), b / g + min_distance(a, b / g));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << min_distance(a, b) << '\n';
    }

    return 0;
}
