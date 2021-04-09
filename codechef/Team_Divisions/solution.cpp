#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll M = 998244353LL;
static constexpr ll LIM = 1e9;

constexpr ll pow_mod(const ll base, const ll exp) {
    if (!exp) return 1;
    if (exp % 2) return (base * pow_mod(base, exp - 1)) % M;
    const ll q = pow_mod(base, exp / 2);
    return (q * q) % M;
}

vll prefix_lcms(const vector<pii> &xys) {
    vll ans(sz(xys), xys[0].first);

    for (int i = 1; i < sz(xys); ++i) {
        ans[i] = (ans[i - 1] > LIM || xys[i].first > LIM)
                     ? 0
                     : lcm(ans[i - 1], llof(xys[i].first));
    }

    return ans;
}

vll suffix_gcds(const vector<pii> &xys) {
    vll ans(sz(xys), xys.back().first);

    for (int i = sz(xys) - 2; i >= 0; --i) {
        ans[i] = gcd(llof(xys[i].first), ans[i + 1]);
    }

    return ans;
}

int divisions_num(const vector<pii> &xys) {
    const auto pref = prefix_lcms(xys);
    const auto suff = suffix_gcds(xys);

    ll ans{};

    for (int i = 0; i < sz(xys) - 1; ++i) {
        const ll left = pref[i];
        if (!left) break;
        const ll right = suff[i + 1];

        if (right % left == 0) {
            ans += pow_mod(2, xys[i].second) - 1;
            ans %= M;
        }
    }

    return inof(ans);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<pii> xys(n);
        for (auto &[x, y] : xys) cin >> x >> y;

        sort(begin(xys), end(xys));
        cout << divisions_num(xys) << '\n';
    }

    return 0;
}
