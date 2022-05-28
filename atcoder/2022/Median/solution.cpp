#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int a, b, c;
    cin >> a >> b >> c;

    array<int, 3> xs{a, b, c};
    sort(begin(xs), end(xs));

    const auto yes = b == xs[1];
    cout << (yes ? "Yes" : "No") << '\n';

    return 0;
}
