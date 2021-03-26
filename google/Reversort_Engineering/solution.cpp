#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    if (xs.empty()) {
        cout << "IMPOSSIBLE";
        return os;
    }

    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vi extra_costs(const int n, const int c) {
    int rest = c - (n - 1);
    vi ans(n - 1, 0);

    for (int i = 0; i < sz(ans); ++i) {
        ans[i] = min(i + 1, rest);
        rest -= ans[i];
        assert(rest >= 0);
    }

    assert(rest == 0);

    reverse(begin(ans), end(ans));
    return ans;
}

int sorting_cost(vi xs) {
    int ans = 0;
    assert(!xs.empty());

    for (auto it = begin(xs); it != prev(end(xs)); ++it) {
        const auto jt = min_element(it, end(xs));

        ans += inof(distance(it, jt)) + 1;
        reverse(it, next(jt));
    }

    return ans;
}

vi solve(const int n, const int c) {
    if (c < n - 1 || c > (n - 1) * (n + 2) / 2) return {};

    const auto cs = extra_costs(n, c);
    vi xs(n);
    iota(begin(xs), end(xs), 1);

    for (int i = n - 2; i >= 0; --i) {
        reverse(begin(xs) + i, begin(xs) + i + cs[i] + 1);
    }

    // assert(sorting_cost(xs) == c);
    return xs;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n, c;
        cin >> n >> c;
        cout << "Case #" << i << ": " << solve(n, c) << '\n';
    }

    return 0;
}
