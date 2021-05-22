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

static constexpr int N_MAX = 100000;

array<int, N_MAX + 1> gather_freqs(const vi &xs) {
    array<int, N_MAX + 1> ans{};
    for (const auto &x : xs) ++ans[x];
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    vi a(n);
    for (auto &x : a) {
        cin >> x;
    }

    vi b(n);
    for (auto &x : b) {
        cin >> x;
    }

    vi c(n);
    for (auto &x : c) {
        cin >> x;
        --x;
    }

    const auto cf = gather_freqs(c);
    array<int, N_MAX + 1> bf{};

    for (int i = 0; i < n; ++i) {
        bf[b[i]] += cf[i];
    }

    ll ans = 0;

    for (const auto x : a) {
        ans += bf[x];
    }

    cout << ans << '\n';
    return 0;
}
