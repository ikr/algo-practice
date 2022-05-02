#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int INF = 1e9;

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int min_shots(const vector<int> &xs) {
    vector<int> one(sz(xs), INF);
    for (int i = 0; i < sz(xs); ++i) {
        one[i] = div_ceil(xs[i], 2);
    }

    partial_sort(begin(one), begin(one) + 2, end(one));

    int two = INF;
    for (int i = 0; i < sz(xs); ++i) {
        const auto a = (i > 0) ? xs[i - 1] : INF;
        const auto b = div_ceil(xs[i], 2);
        const auto c = (i < sz(xs) - 1) ? xs[i + 1] : INF;

        vector ops{a, b, c};
        sort(begin(ops), end(ops));
        two = min(two, ops[1]);
    }

    int nei = INF;
    for (int i = 1; i < sz(xs); ++i) {
        auto a = xs[i - 1];
        auto b = xs[i];

        if (a > b) swap(a, b);
        const auto k = div_ceil(2 * b - a, 3);
        const auto p = div_ceil(a - k, 2);
        nei = min(nei, k + p);
    }

    return min({one[0] + one[1], two, nei});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    cout << min_shots(xs) << '\n';
    return 0;
}
