#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> sorted_indices(const vector<int> &xs) {
    const auto n = sz(xs);
    vector<int> ans(n);
    iota(begin(ans), end(ans), 0);
    sort(begin(ans), end(ans),
         [&](const int i, const int j) { return xs[i] < xs[j]; });
    return ans;
}

vector<int> actual_ts(const int k, const vector<int> &xs,
                      const vector<int> &ys) {
    const auto ix = sorted_indices(xs);
    const auto iy = sorted_indices(ys);

    const auto n = sz(xs);
    vector<int> ans(n, 0);

    for (int i = 0; i < n; ++i) {
        ans[ix[i]] = ys[iy[i]];
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        vector<int> ys(n);
        for (auto &y : ys) cin >> y;

        cout << actual_ts(k, xs, ys) << '\n';
    }

    return 0;
}
