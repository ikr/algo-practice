#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    const auto vs = count(cbegin(xs), cend(xs), 'v');
    const auto ws = sz(xs) - vs;

    cout << (vs + ws * 2) << '\n';
    return 0;
}
