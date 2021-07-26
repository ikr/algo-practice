#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll INF = 1e18;

vll ltr_moves(const string &xs) {
    vi pref(sz(xs), 0);
    if (xs[0] == '*') pref[0] = 1;

    vll ans(sz(xs), 0);

    for (int i = 1; i < sz(xs); ++i) {
        pref[i] = pref[i - 1] + (xs[i] == '*' ? 1 : 0);

        ans[i] = ans[i - 1];
        if (xs[i] == '.') ans[i] += pref[i - 1];
    }

    return ans;
}

vll rtl_moves(const string &xs) {
    vi suff(sz(xs), 0);
    if (xs.back() == '*') suff.back() = 1;

    vll ans(sz(xs), 0);

    for (int i = sz(xs) - 2; i >= 0; --i) {
        suff[i] = suff[i + 1] + (xs[i] == '*' ? 1 : 0);

        ans[i] = ans[i + 1];
        if (xs[i] == '.') ans[i] += suff[i + 1];
    }

    return ans;
}

ll min_moves(const string &xs) {
    const auto ltr = ltr_moves(xs);
    const auto rtl = rtl_moves(xs);

    ll ans = INF;

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == '.') continue;

        const ll l = i == 0 ? 0LL : ltr[i - 1];
        const ll r = i == sz(xs) - 1 ? 0LL : rtl[i + 1];
        ans = min(ans, l + r);
    }

    return ans == INF ? 0 : ans;
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

        string xs(n, ' ');
        cin >> xs;

        cout << min_moves(xs) << '\n';
    }

    return 0;
}
