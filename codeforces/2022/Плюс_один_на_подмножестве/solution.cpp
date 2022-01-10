#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll min_ops(const vi &xs) {
    ll ans{};
    int d{};

    for (int i = sz(xs) - 2; i >= 0; --i) {
        const auto d_ = xs.back() - (xs[i] + d);
        d += d_;
        ans += d_;
    }

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
        vi xs(n, 0);

        for (auto &x : xs) cin >> x;

        sort(begin(xs), end(xs));
        xs.erase(unique(begin(xs), end(xs)), end(xs));
        cout << min_ops(xs) << '\n';
    }

    return 0;
}
