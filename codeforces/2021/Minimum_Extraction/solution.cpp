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

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<ll, int> gather_freqs(const vll &xs) {
    map<ll, int> ans;
    for (const auto x : xs) ++ans[x];
    return ans;
}

ll maximin(const vll &xs) {
    if (sz(xs) == 1) return xs[0];

    auto fs = gather_freqs(xs);
    ll ans = cbegin(fs)->first;
    ll corr = 0LL;

    while (sz(fs) > 1 || (sz(fs) == 1 && cbegin(fs)->second > 1)) {
        const ll x = cbegin(fs)->first - corr;
        --(begin(fs)->second);
        if (cbegin(fs)->second == 0) fs.erase(cbegin(fs));

        corr += x;
        ans = max(ans, cbegin(fs)->first - corr);
    }

    ans = max(ans, cbegin(fs)->first - corr);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vll xs(n);

        for (auto &x : xs) cin >> x;
        cout << maximin(xs) << '\n';
    }

    return 0;
}
