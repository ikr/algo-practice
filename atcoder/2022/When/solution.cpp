#include <iostream>
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

    const auto h = 21 + t / 60;
    const auto m = t % 60;

    cout << h << ':' << (m > 9 ? "" : "0") << m << '\n';
    return 0;
}
