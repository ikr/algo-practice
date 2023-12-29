#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

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
        return pair{lhs, lhs.second - lhs.first} <
               pair{rhs, rhs.second - rhs.first};
    });

    int result{};
    ordered_set<int> as;
    ordered_set<int> bs;
    for (const auto &[a, b] : AB) {
        as.insert(a);
        bs.insert(b);
        result += min(inof(bs.order_of_key(b)),
                      sz(as) - inof(as.order_of_key(a) - 1));
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
