#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
using ordered_set = tree<T, null_type, greater<T>, rb_tree_tag,
                         tree_order_statistics_node_update>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ordered_set<pii> xs;

    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;

        xs.insert(pii{x, t});
        const auto it = xs.find_by_order(sz(xs) / 2);
        cout << it->first << ' ';
    }
    cout << '\n';

    return 0;
}
