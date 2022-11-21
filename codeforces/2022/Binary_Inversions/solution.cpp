#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll best_attained_inversions(const vector<int> &xs) {
    const auto n = sz(xs);
    vector<int> ss1(n);
    partial_sum(cbegin(xs), cend(xs), begin(ss1));

    const auto ones_within = [&](const int a, const int b) {
        if (a > b) return 0;
        return ss1[min(b, n - 1)] - (a > 0 ? ss1[a - 1] : 0);
    };

    vector<int> ss0(n, xs[0] == 0);
    for (int i = 1; i < n; ++i) {
        ss0[i] = ss0[i - 1] + (xs[i] == 0);
    }

    const auto zeros_within = [&](const int a, const int b) {
        if (a > b) return 0;
        return ss0[min(b, n - 1)] - (a > 0 ? ss0[a - 1] : 0);
    };

    ll baseline{};
    for (int i = 0; i < n - 1; ++i) {
        if (xs[i] == 1) {
            baseline += zeros_within(i + 1, n - 1);
        }
    }

    ll result = baseline;

    for (int i = 0; i < n; ++i) {
        if (xs[i] == 1) {
            result = max(result, baseline - zeros_within(i + 1, n - 1) +
                                     ones_within(0, i - 1));
        } else {
            assert(xs[i] == 0);
            result = max(result, baseline - ones_within(0, i - 1) +
                                     zeros_within(i + 1, n - 1));
        }
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

        cout << best_attained_inversions(xs) << '\n';
    }

    return 0;
}
