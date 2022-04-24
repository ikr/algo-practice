#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int division(const int x) {
    if (x >= 1900) return 1;
    if (x >= 1600) return 2;
    if (x >= 1400) return 3;
    return 4;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        cout << "Division " << division(n) << '\n';
    }

    return 0;
}
