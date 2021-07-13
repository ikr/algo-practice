#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using invl = pair<ll, ll>;

ll solve_quadratic(const vector<invl> &lrs, ll budget) {
    const auto [leftmost, rightmost] = [&]() -> pair<ll, ll> {
        ll lo = LONG_LONG_MAX;
        ll hi = LONG_LONG_MIN;

        for (const auto [l, r] : lrs) {
            lo = min(lo, l);
            hi = max(hi, r);
        }

        return {lo, hi};
    }();

    const auto properly_containing_ingtervals = [&](const ll x) -> int {
        int ans = 0;
        for (const auto [l, r] : lrs) {
            if (l < x && x < r) ++ans;
        }
        return ans;
    };

    priority_queue<int> pq;
    for (auto x = leftmost; x <= rightmost; ++x) {
        const int cuts = properly_containing_ingtervals(x);
        if (cuts) pq.push(cuts);
    }

    ll ans = sz(lrs);
    ;
    while (!pq.empty() && budget > 0) {
        ans += pq.top();
        pq.pop();
        --budget;
    }
    return ans;
}

pair<map<ll, int>, map<ll, int>>
gather_balance_and_openings(const vector<invl> &lrs) {
    map<ll, int> openings;
    map<ll, int> closings;
    set<ll> milestones;

    for (const auto [l, r] : lrs) {
        ++openings[l];
        ++closings[r];
        milestones.insert(l);
        milestones.insert(r);
    }

    map<ll, int> bal;
    bal[*cbegin(milestones)] = openings[*cbegin(milestones)];

    for (auto it = next(cbegin(milestones)); it != cend(milestones); ++it) {
        bal[*it] = bal.at(*prev(it)) + openings[*it] - closings[*it];
    }

    assert(crbegin(bal)->second == 0);
    return {bal, openings};
}

ll solve(const vector<invl> &lrs, ll budget) {
    const auto [bal, openings] = gather_balance_and_openings(lrs);
    const ll rightmost = crbegin(bal)->first;

    // additional intervals per cut, max number of cuts
    priority_queue<pair<ll, ll>> pq;
    for (const auto [x, num] : bal) {
        if (x == rightmost) continue;

        const auto y = bal.upper_bound(x)->first;
        const ll inner_cuts = y - x - 1LL;
        assert(inner_cuts >= 0);

        if (inner_cuts > 0) {
            pq.emplace(num, inner_cuts);
        }

        const auto inside = num - openings.at(x);
        if (inside > 0) {
            pq.emplace(inside, 1);
        }
    }

    ll ans = sz(lrs);

    while (!pq.empty() && budget > 0LL) {
        const auto [additions_per_cut, cuts] = pq.top();
        pq.pop();

        const auto cutting = min(cuts, budget);
        ans += cutting * additions_per_cut;
        budget -= cutting;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;

        ll c;
        cin >> c;

        vector<invl> lrs(n);
        for (auto &[l, r] : lrs) cin >> l >> r;

        cout << "Case #" << i << ": " << solve(lrs, c)
             << '\n'; //<< ", " << solve_quadratic(lrs, c) << '\n';
    }

    return 0;
}
