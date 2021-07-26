#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T> struct mmax final {
    constexpr T operator()(const T &a, const T &b) const {
        return std::max(a, b);
    }
};

vector<ll> partial_maxes(const vector<ll> &xs) {
    const int n = xs.size();
    vector<ll> mxs(n);
    partial_sum(cbegin(xs), cend(xs), begin(mxs), mmax<ll>{});
    return mxs;
}

vector<ll> max_prods(const vector<ll> &xs, const vector<ll> &ys) {
    const int n = xs.size();
    vector<ll> mxs = partial_maxes(xs);

    vector<ll> ans(n, xs[0] * ys[0]);
    for (int i = 1; i < n; ++i) {
        ans[i] = max(ans[i - 1], ys[i] * mxs[i]);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<ll> xs(n);
    for (auto &x : xs) cin >> x;

    vector<ll> ys(n);
    for (auto &y : ys) cin >> y;

    for (const auto c : max_prods(xs, ys)) {
        cout << c << '\n';
    }

    return 0;
}
