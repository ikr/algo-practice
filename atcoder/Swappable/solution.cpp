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

map<int, int> gather_freqs(const vi &xs) {
    map<int, int> ans;
    for (const auto &x : xs) ++ans[x];
    return ans;
}

ll proper_pairs_num(const vi &xs) {
    const auto fs = gather_freqs(xs);
    ll ans = 0;
    for (const auto [_, f] : fs) {
        ans += llof(f) * (sz(xs) - llof(f));
    }
    return ans / 2LL;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    vi xs(n);
    for (auto &x : xs) cin >> x;

    cout << proper_pairs_num(xs) << '\n';
    return 0;
}
