#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

int dist(const char x, const char y) {
    if (x == y) return 0;
    if (x == '0') return 10 - (y - '0');
    if (y == '0') return 10 - (x - '0');
    return abs(inof(x) - inof(y));
}

int pin_time(const string &xs) {
    int result{};
    char cur = '1';
    for (const auto x : xs) {
        result += dist(cur, x);
        ++result;
        cur = x;
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        cout << pin_time(xs) << '\n';
    }

    return 0;
}
