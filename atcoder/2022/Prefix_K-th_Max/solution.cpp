#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    vi xs(n, 0);
    for (auto &x : xs) cin >> x;

    ordered_set<int> s(cbegin(xs), cbegin(xs) + k);
    const auto curr = [&]() -> int { return *(s.find_by_order(sz(s) - k)); };

    cout << curr() << '\n';

    for (int i = k; i < n; ++i) {
        s.insert(xs[i]);
        cout << curr() << '\n';
    }

    return 0;
}
