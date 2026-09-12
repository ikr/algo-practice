#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using tri = tuple<int, int, int>;

tri operator+(const tri &a, const tri &b) {
    const auto [x, y, z] = a;
    const auto [i, j, k] = b;
    return {x + i, y + j, z + k};
}

tri change(const int x) {
    const int a = x / 100;
    const int b = (x % 100) / 10;
    const int c = x % 10;
    return {a, b, c};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    tri coins{0, 0, 0};

    for (int i = 0; i != n; ++i) {
        int x;
        cin >> x;
        coins = coins + change(1000 - (x % 1000));
    }

    const auto [a, b, c] = coins;
    cout << c << ' ' << b << ' ' << a << '\n';
    return 0;
}
