#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

using namespace __gnu_pbds;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int num_greetings(vector<pii> AB) {
    ranges::sort(AB, [](const auto &lhs, const auto &rhs) {
        return lhs.second - lhs.first < rhs.second - rhs.first;
    });

    int result{};
    ordered_set<int> bs;
    for (const auto &[a, b] : AB) {
        bs.insert(b);
        result += inof(bs.order_of_key(b));
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<pii> AB(n);
        for (auto &[a, b] : AB) cin >> a >> b;
        cout << num_greetings(std::move(AB)) << '\n';
    }

    return 0;
}
