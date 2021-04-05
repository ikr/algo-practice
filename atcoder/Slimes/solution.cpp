#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Iter = vll::const_iterator;

ll min_cost(const vll &xs) {
    vll ss(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    const auto sum_up = [&](const Iter first, const Iter last) {
        return ss[distance(cbegin(xs), last) - 1] -
               (first == cbegin(xs) ? 0 : ss[distance(cbegin(xs), first) - 1]);
    };

    map<pair<Iter, Iter>, ll> memo;

    function<ll(Iter, Iter)> recur;

    recur = [&](const Iter first, const Iter last) -> ll {
        if (memo.count({first, last})) return memo.at({first, last});

        assert(first < last);
        if (distance(first, last) < 2) return 0;

        ll ans = 1e18;
        const ll s = sum_up(first, last);

        for (auto cut = next(first); cut != last; ++cut) {
            ans = min(ans, recur(first, cut) + recur(cut, last) + s);
        }

        memo[{first, last}] = ans;
        return ans;
    };

    return recur(cbegin(xs), cend(xs));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;
    vll xs(n);
    for (auto &x : xs) cin >> x;

    cout << min_cost(xs) << '\n';
    return 0;
}
