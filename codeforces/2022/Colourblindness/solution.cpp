#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

void normalize(string &xs) {
    transform(cbegin(xs), cend(xs), begin(xs), [](const char x) {
        if (x == 'G' || x == 'B') return '.';
        return x;
    });
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs, ys;
        cin >> xs >> ys;

        normalize(xs);
        normalize(ys);

        const auto yes = xs == ys;
        cout << (yes ? "YES" : "NO") << '\n';
    }

    return 0;
}
