#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll min_ops(const vector<int> &xs) {
    const auto n = sz(xs);
    if (n == 1) return 0;

    vector<int> ds(n / 2);
    for (int i = 0; i < n / 2; ++i) {
        ds[i] = xs[n - 1 - i] - xs[i];
    }

    for (int i = 0; i < sz(ds); ++i) {
        if (ds[i] < 0) return -1;
        if (i && ds[i - 1] < ds[i]) return -1;
    }

    assert(!ds.empty());
    vector<int> dds{ds[0]};

    for (int i = 1; i < sz(ds); ++i) {
        if (dds.back() == ds[i]) continue;
        dds.push_back(ds[i]);
    }

    ll result{};
    for (int i = 0; i < sz(dds) - 1; ++i) {
        result += dds[i] - dds[i + 1];
    }
    result += dds.back();
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << min_ops(xs) << '\n';
    }

    return 0;
}
