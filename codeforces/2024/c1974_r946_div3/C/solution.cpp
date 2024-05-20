#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using tri = tuple<int, int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll bpairs_num(const vector<int> &xs) {
    map<tri, int> fp;
    map<tri, int> ft;

    ll result{};

    for (int i2 = 2; i2 < sz(xs); ++i2) {
        const auto i0 = i2 - 2;
        const auto i1 = i2 - 1;
        const auto a = xs[i0];
        const auto b = xs[i1];
        const auto c = xs[i2];

        result += 0LL + fp[{a, b, 0}] + fp[{0, b, c}] + fp[{a, 0, c}] -
                  3LL * ft[{a, b, c}];

        ++fp[{a, b, 0}];
        ++fp[{0, b, c}];
        ++fp[{a, 0, c}];
        ++ft[{a, b, c}];
    }

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

        cout << bpairs_num(xs) << '\n';
    }

    return 0;
}
