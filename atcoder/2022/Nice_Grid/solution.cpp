#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int R, C;
    cin >> R >> C;
    --R;
    --C;

    const auto cheb = max(abs(R - 7), abs(C - 7));
    cout << (cheb % 2 ? "black" : "white") << '\n';

    return 0;
}
