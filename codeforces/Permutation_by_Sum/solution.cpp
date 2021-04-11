#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

pii lower_bound_pos(const int n, const int d, const int s) {
    for (int i = 1; i <= n; ++i) {
        const int curr = d * (i + i + d - 1) / 2;
        if (curr >= s) return {i, curr};
    }

    assert(false && "lower_bound_pos");
    return {-1, -1};
}

vi solution(const int n, const int l, const int r, const int s) {
    const int d = r - l + 1;
    const int s_lo = d * (1 + d) / 2;
    const int s_hi = d * (n - d + 1 + n) / 2;

    if (s < s_lo || s > s_hi) return {};

    vi ans(n, 0);
    const auto [start, s0] = lower_bound_pos(n, d, s);
    for (int i = start; i < start + d; ++i) {
        ans[l + i - start - 1] = i;
    }

    set<int> av;
    for (int i = 1; i <= n; ++i) av.insert(i);
    for (const int x : ans) av.erase(x);

    for (auto &x : ans) {
        if (!x) {
            assert(!av.empty());
            x = *cbegin(av);
            av.erase(cbegin(av));
        }
    }

    if (s == s0) return ans;
    assert(s0 > s);

    for (int i = l; i <= r; ++i) {
        for (int p = 1; p <= n; ++p) {
            if (l <= p && p <= r) continue;

            int s_prime = s0 - ans[i - 1] + ans[p - 1];
            if (s_prime == s) {
                swap(ans[i - 1], ans[p - 1]);
                return ans;
            }
        }
    }

    assert(false && "solution()");
    return {};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n, l, r, s;
        cin >> n >> l >> r >> s;

        const auto ans = solution(n, l, r, s);
        if (ans.empty()) {
            cout << "-1\n";
        } else {
            cout << ans << '\n';
        }
    }

    return 0;
}
