#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_inversions(const vi &xs) {
    vi ys = xs;
    sort(begin(ys), end(ys));
    ys.erase(unique(begin(ys), end(ys)), end(ys));

    unordered_map<int, int> idx;
    for (int i = 0; i < sz(ys); ++i) idx[ys[i]] = i;

    int ans = 0;
    int t = 0;
    ordered_set<pii> q;

    for (const auto x : xs) {
        const auto ord = idx.at(x);

        if (q.empty()) {
            q.insert({ord, t++});
            continue;
        }

        const auto it = q.lower_bound(pii{ord, 0});
        const auto jt = q.upper_bound(pii{ord, t + 1});

        const auto k = sz(q);

        ans += min(it == cend(q) ? k : inof(q.order_of_key(*it)),
                   jt == cend(q) ? 0 : k - inof(q.order_of_key(*jt)));
        q.insert({ord, t++});
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;

        cout << min_inversions(xs) << '\n';
    }

    return 0;
}
