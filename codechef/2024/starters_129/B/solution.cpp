#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int winner_index(const string &xs) {
    const auto n = sz(xs);
    const auto ones = inof(count(cbegin(xs), cend(xs), '1'));
    const auto zeros = inof(count(cbegin(xs), cend(xs), '0'));

    if (ones && zeros) {
        if (n == 2) return 1;
        return !((n - 3) % 2);
    } else {
        return n % 2;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        cout << (winner_index(xs) ? "Bob" : "Alice") << '\n';
    }

    return 0;
}
