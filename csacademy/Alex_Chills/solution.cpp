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

int max_level(vi xs, const int l, const int r) {
    const int total =
        accumulate(cbegin(xs), cend(xs), 0,
                   [](const int agg, const int x) { return agg ^ x; });

    xs.insert(cend(xs), total);
    const int m = sz(xs);

    if (r - l + 1 >= m) return *max_element(cbegin(xs), cend(xs));

    int ans = 0;

    for (int i = l % m;;) {
        ans = max(ans, xs[i]);
        if (i == r % m) break;
        ++i;
        i %= m;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n, l, r;
    cin >> n >> l >> r;

    --l;
    --r;

    vi xs(n);
    for (auto &x : xs) cin >> x;

    cout << max_level(xs, l, r) << '\n';
    return 0;
}
