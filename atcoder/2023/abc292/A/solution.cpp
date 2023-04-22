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

    transform(cbegin(xs), cend(xs), begin(xs),
              [](const char x) -> char { return toupper(x); });
    cout << xs << '\n';

    return 0;
}
