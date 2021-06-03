#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

static constexpr ll INF = 1e17;

ll max_score(const vll &xs) {
    ll ans = -INF;
    ll curr = 0;

    for (const auto x : xs) {
        curr = max(curr + x, x);
        ans = max(curr, ans);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vll xs(n);
        for (auto &x : xs) cin >> x;

        cout << max_score(xs) << '\n';
    }

    return 0;
}
