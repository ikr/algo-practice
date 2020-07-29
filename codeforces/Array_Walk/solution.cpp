#include <bits/stdc++.h>
#include <climits>
using namespace std;

int max_pair_index(const vector<int> &xs, const int sz) {
    int ans = 0;
    int hi = xs[0] + xs[1];

    for (int i = 1; i < sz - 1; ++i) {
        const int candidate = xs[i] + xs[i + 1];
        if (candidate > hi) {
            ans = i;
            hi = candidate;
        }
    }

    return ans;
}

int best_score(const vector<int> &xs, const int k, const int z) {
    if (k <= 0) return INT_MIN;
    const int ans = accumulate(xs.cbegin(), xs.cbegin() + k + 1, 0);
    if (z == 0) return ans;

    int candidate1 = INT_MIN;
    if (k - 2 >= 0) {
        candidate1 = xs[k - 2] + best_score(xs, k - 1, z - 1);
    }

    int candidate2 = INT_MIN;
    if (k > 1) {
        const int hi = max_pair_index(xs, k - 1);
        candidate2 = xs[hi] + xs[hi + 1] + best_score(xs, k - 2, z - 1);
    }

    return max({ans, candidate1, candidate2});
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, k, z;
        cin >> n >> k >> z;

        vector<int> xs(n, 0);
        for (auto &x : xs) {
            cin >> x;
        }

        cout << best_score(xs, k, z) << '\n';
    }

    return 0;
}
