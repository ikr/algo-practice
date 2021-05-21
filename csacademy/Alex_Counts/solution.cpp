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

vi gather_freqs(const vi &xs) {
    const int hi = *max_element(cbegin(xs), cend(xs));
    vi ans(hi + 1, 0);
    for (const auto x : xs) ++ans[x];
    return ans;
}

ll combos_num(const vi &xs) {
    const auto fs = gather_freqs(xs);
    ll ans = 0;

    for (const auto x : xs) {
        // if (fs[1]) {
        //     if (x == 1) {
        //         const ll n = fs[1] - 1LL;
        //         ans += n * (n - 1LL) / 2LL;
        //     } else if (fs[x] > 1) {
        //         ans += fs[1] * (fs[x] - 1);
        //     }
        // }

        for (int i = 2; i <= inof(sqrt(x)); ++i) {
            if (x % i || !fs[i]) continue;

            const int q = x / i;
            if (!fs[q]) continue;

            if (q == i) {
                // ans += llof(fs[i]) * (fs[i] - 1LL) / 2LL;
            } else {
                ans += llof(fs[i]) * fs[q];
            }
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    vi xs(n);
    for (auto &x : xs) cin >> x;

    cout << combos_num(xs) << '\n';
    return 0;
}
