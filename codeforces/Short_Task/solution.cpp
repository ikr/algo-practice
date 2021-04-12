#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi min_prime_factors(const int hi) {
    vi lp(hi + 1, 0);
    vi pr;

    for (int i = 2; i <= hi; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }

        for (int j = 0; j < sz(pr) && pr[j] <= lp[i] && i * pr[j] <= hi; ++j) {
            lp[i * pr[j]] = pr[j];
        }
    }

    return lp;
}

constexpr ll mpow(const ll base, const ll exp) {
    if (!exp) return 1LL;
    if (exp % 2LL) return base * mpow(base, exp - 1LL);
    const ll q = mpow(base, exp / 2LL);
    return q * q;
}

ll sigma(const vi &lp, const int x) {
    if (x == 1) return 1;
    if (lp[x] == x) return x + 1;

    int e = 1;
    while (llof(x) % mpow(lp[x], e + 1) == 0) ++e;

    const ll lhs = (mpow(lp[x], e + 1) - 1) / (lp[x] - 1);
    return lhs * sigma(lp, x / inof(mpow(lp[x], e)));
}

vi min_ns_by_signma(const vi &lp) {
    vi ans(sz(lp), -1);

    for (int x = 1; x < sz(lp); ++x) {
        const auto s = sigma(lp, x);
        if (s < sz(lp) && ans[inof(s)] == -1) ans[inof(s)] = x;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const auto ans = min_ns_by_signma(min_prime_factors(1e7));

    int t;
    cin >> t;
    while (t--) {
        int c;
        cin >> c;

        cout << ans[c] << '\n';
    }

    return 0;
}
