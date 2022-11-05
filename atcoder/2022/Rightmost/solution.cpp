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

    const auto i = xs.rfind('a');
    cout << (i == xs.npos ? string{"-1"} : to_string(i + 1)) << '\n';

    return 0;
}
