#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int intof(const T x) {
    return static_cast<int>(x);
}

int solve(const vector<int> &xs, const int k) {
    const int n = xs.size();
    vector<multiset<int>> trees(n);
    trees[0].insert(xs[0]);

    for (int i = 1; i < n; ++i) {
        trees[i] = trees[i - 1];
        trees[i].insert(xs[i]);
    }

    int ans = 1;

    for (int i = 1; i < n; ++i) {
        const auto tree = trees[i - 1];
        const auto lo = tree.lower_bound(max(0, xs[i] - k));
        const auto hi = tree.upper_bound(xs[i] + k);
        ans = max(ans, intof(distance(lo, hi)));
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, K;
    cin >> N >> K;

    vector<int> xs(N, 0);
    for (auto &x : xs) cin >> x;

    cout << solve(xs, K) << '\n';

    return 0;
}
