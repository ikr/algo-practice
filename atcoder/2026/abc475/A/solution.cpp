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

    const int n = sz(xs);
    for (int i = 0; i != n; ++i) {
        cout << xs[i];

        if (i != n - 1) {
            cout << 'o';
        }
    }
    cout << '\n';

    return 0;
}
