#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int a, b, c, d;
    cin >> a >> b >> c >> d;

    cout << ((a + b) * (c - d)) << '\n';
    cout << "Takahashi\n";

    return 0;
}
