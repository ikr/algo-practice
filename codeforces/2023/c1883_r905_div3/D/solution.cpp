#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    map<int, multiset<pii>> by_l;
    map<int, multiset<pii>> by_r;

    int T;
    cin >> T;
    while (T--) {
        char op;
        cin >> op;

        int l, r;
        cin >> l >> r;

        const auto has_non_intersecting_pair = false;
        cout << (has_non_intersecting_pair ? "NO" : "YES") << '\n';
    }

    return 0;
}
