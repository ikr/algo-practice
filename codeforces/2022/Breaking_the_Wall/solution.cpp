#include <algorithm>
#include <iostream>
#include <iterator>
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
    const auto o1 = [&]() -> int {
        vector<int> ys(2);
        partial_sort_copy(cbegin(xs), cend(xs), begin(ys), end(ys));
        return div_ceil(ys[0], 2) + div_ceil(ys[1], 2);
    }();

    const auto o2 = [&]() -> int {
        int result = INF;
        for (int i = 0; i < sz(xs); ++i) {
            const auto a = (i > 0) ? xs[i - 1] : INF;
            const auto b = div_ceil(xs[i], 2);
            const auto c = (i < sz(xs) - 1) ? xs[i + 1] : INF;

            vector ops{a, b, c};
            sort(begin(ops), end(ops));
            result = min(result, ops[1]);
        }
        return result;
    }();

    const auto o3 = [&]() -> int {
        int result = INF;
        for (int i = 1; i < sz(xs); ++i) {
            result = min(result, div_ceil(xs[i - 1] + xs[i], 2));
        }
        return result;
    }();

    return min({o1, o2, o3});
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
