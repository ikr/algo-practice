#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int max_teleports_from_left_only(const int c, const vector<int> &xs) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < sz(xs); ++i) {
        pq.push(i + 1 + xs[i]);
    }

    int ans{};
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

    vector<ll> lcs_psums(sz(lcs));
    partial_sum(cbegin(lcs), cend(lcs), begin(lcs_psums));
    vector<ll> rcs_psums(sz(rcs));
    partial_sum(cbegin(rcs), cend(rcs), begin(rcs_psums));

    int ans = max_teleports_from_left_only(c, xs);
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
