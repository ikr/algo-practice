#include <bits/stdc++.h>
using namespace std;

static constexpr int INF = INT_MAX;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int opt_mid_left(vector<int> xs) {
    const auto target = xs[0] + xs.back();
    xs.insert(begin(xs) + sz(xs) / 2, 0);
    const auto n = sz(xs);
    xs[n / 2 - 1] = target - xs[n / 2];
    if (xs[n / 2 - 1] <= 0) return INF;

    for (int i = n / 2 - 1, j = n / 2; i >= 0 && j < n; --i, ++j) {
        if (xs[i] + xs[j] != target) return INF;
    }

    return xs[n / 2 - 1];
}

int min_possible_apple_weight(const vector<int> &xs) {
    if (sz(xs) == 1) return 1;
    int result = opt_mid_left(xs);
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<int> xs(2 * N - 1);
        ranges::sort(xs);
        for (auto &x : xs) cin >> x;

        const auto ans = min_possible_apple_weight(xs);
        cout << "Case #" << i << ": " << (ans == INF ? -1 : ans) << '\n';
    }

    return 0;
}
