#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using invl = pair<ll, ll>;

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

    return {bal, openings};
}

ll solve(const vector<invl> &lrs, ll budget) {
    const auto [bal, openings] = gather_balance_and_openings(lrs);
    const ll leftmost = cbegin(bal)->first;
    const ll rightmost = crbegin(bal)->first;

    priority_queue<pair<int, ll>> pq;
    for (const auto [x, num] : bal) {
        if (x == leftmost || x == rightmost) continue;
        pq.emplace(num, x);
    }

    ll ans = sz(lrs);

    while (!pq.empty() && budget > 0LL) {
        const auto [num, x] = pq.top();
        pq.pop();

        const auto y = bal.upper_bound(x)->first;
        const ll inner_cuts = min(y - x - 1LL, budget);

        if (inner_cuts > 0LL) {
            ans += (inner_cuts + 1) * num - num;
            budget -= inner_cuts;
        }
    }

    if (budget == 0LL) return ans;
    assert(pq.empty());

    for (const auto [x, num] : bal) {
        if (x == leftmost || x == rightmost) continue;

        const auto inside = num - openings.at(x);
        if (inside <= 0) continue;

        pq.emplace(inside, x);
    }

    while (!pq.empty() && budget > 0LL) {
        const auto [inside, x] = pq.top();
        pq.pop();

        ans += (inside * 2) - inside;
        --budget;
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

        cout << "Case #" << i << ": " << solve(lrs, c) << '\n';
    }

    return 0;
}
