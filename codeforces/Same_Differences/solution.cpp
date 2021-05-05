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

ll proper_pairs_num(const vi &xs) {
    map<int, int> di_freqs;

    for (int i = 0; i < sz(xs); ++i) {
        const int pos = i + 1;
        const int x = xs[i];
        const int di = x - pos;

        ++di_freqs[di];
    }

    ll ans = 0;

    for (const auto [_, num] : di_freqs) {
        ans += llof(num) * (llof(num) - 1LL) / 2LL;
    }

    return ans;
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

        vi xs(n);
        for (auto &x : xs) cin >> x;

        cout << proper_pairs_num(xs) << '\n';
    }

    return 0;
}
