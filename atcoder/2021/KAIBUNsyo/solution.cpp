#include <atcoder/dsu>
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

vi distinct_values(const vi &xs) {
    set<int> xss(cbegin(xs), cend(xs));
    return vi(cbegin(xss), cend(xss));
}

int min_ops(const vi &xs) {
    const auto ds = distinct_values(xs);
    atcoder::dsu t(sz(ds));

    const auto index = [&](const int x) -> int {
        return inof(distance(cbegin(ds), lower_bound(cbegin(ds), cend(ds), x)));
    };

    for (int i = 0; i < sz(xs) / 2; ++i) {
        const auto l = xs[i];
        const auto r = xs[sz(xs) - 1 - i];

        if (l == r) continue;

        t.merge(index(l), index(r));
    }

    int ans = 0;
    for (const auto &c : t.groups()) {
        ans += sz(c) - 1;
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

    cout << min_ops(xs) << '\n';
    return 0;
}
