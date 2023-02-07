#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_right_teleports_afetr_one_walk_from_left(int c, const vector<int> &xs) {
    int ilo = 0;
    int lo = 1 + xs[0];
    for (int i = 1; i < sz(xs); ++i) {
        if (i + 1 + xs[i] < lo) {
            ilo = i;
            lo = i + 1 + xs[i];
        }
    }
    if (c < lo) return 0;

    c -= lo;
    if (c == 0) return 1;

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < sz(xs); ++i) {
        if (i == ilo) continue;
        pq.push(sz(xs) - i + xs[i]);
    }

    int ans = 1;
    auto cur = c;
    while (!pq.empty() && pq.top() <= cur) {
        cur -= pq.top();
        pq.pop();
        ++ans;
    }

    return ans;
}

int max_teleports(const int c, const vector<int> &xs) {
    const auto n = sz(xs);
    const auto im = (n - 1) / 2;

    const auto [lcs_psums, rcs_psums] = [&]() -> pair<vector<ll>, vector<ll>> {
        vector<ll> costs(n);
        for (int i = 0; i <= im; ++i) {
            costs[i] = i + 1 + xs[i];
        }
        for (int i = im + 1; i < n; ++i) {
            costs[i] = n - i + xs[i];
        }

        vector<ll> lcs(cbegin(costs), cbegin(costs) + im + 1);
        sort(begin(lcs), end(lcs));
        vector<ll> rcs(cbegin(costs) + im + 1, cend(costs));
        sort(begin(rcs), end(rcs));

        vector<ll> A(sz(lcs));
        partial_sum(cbegin(lcs), cend(lcs), begin(A));
        vector<ll> B(sz(rcs));
        partial_sum(cbegin(rcs), cend(rcs), begin(B));

        return {A, B};
    }();

    int ans = max_right_teleports_afetr_one_walk_from_left(c, xs);
    for (int i = 0; i <= im; ++i) {
        if (lcs_psums[i] > c) break;
        const auto remaining_for_right = c - lcs_psums[i];
        ans = max(ans, i + 1);
        if (remaining_for_right <= 0) break;

        auto jt = lower_bound(cbegin(rcs_psums), cend(rcs_psums),
                              remaining_for_right + 1);
        if (jt == cbegin(rcs_psums)) {
            continue;
        } else {
            jt = prev(jt);
        }

        const auto j = inof(distance(cbegin(rcs_psums), jt));
        ans = max(ans, i + 1 + j + 1);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, c;
        cin >> n >> c;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << max_teleports(c, xs) << '\n';
    }

    return 0;
}
