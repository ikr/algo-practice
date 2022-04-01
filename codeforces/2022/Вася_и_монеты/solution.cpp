#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int solve(const int a, const int b) {
    if (a == 0) return 1;
    if (b == 0) return a + 1;
    return 2 * b + a + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;

        cout << solve(a, b) << '\n';
    }

    return 0;
}
