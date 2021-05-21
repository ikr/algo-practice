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
        for (int i = 2; i * i <= x; ++i) {
            if (!fs[i] || x % i) continue;

            const int q = x / i;
            if (!fs[q]) continue;

            if (q != i) {
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
