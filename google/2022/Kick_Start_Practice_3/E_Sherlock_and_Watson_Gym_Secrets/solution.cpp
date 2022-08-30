#include <bits/stdc++.h>
using namespace std;

using ll = long long;
static constexpr ll M = 1e9 + 7;

ll modpow(const ll mod, ll b, ll e) {
    ll ans = 1;
    for (; e; b = b * b % mod, e /= 2)
        if (e & 1) ans = ans * b % mod;
    return ans;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int num_pairs(const ll A, const ll B, const ll N, const ll K) {
    ll result{};

    for (ll i = 1; i <= N; ++i) {
        for (ll j = 1; j <= N; ++j) {
            if (i == j) continue;
            if ((modpow(K, i, A) + modpow(K, j, B)) % K == 0LL) ++result;
        }
    }

    return inof(result);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        ll A, B, N, K;
        cin >> A >> B >> N >> K;

        cout << "Case #" << i << ": " << num_pairs(A, B, N, K) << '\n';
    }

    return 0;
}
