#include <bits/stdc++.h>
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
    while (t--) {
        array<int, 3> xs{};
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        cout << xs[1] << '\n';
    }

    return 0;
}
