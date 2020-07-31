#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int intof(const T x) {
    return static_cast<int>(x);
}

vector<int> best_pair_tails(const vector<int> &xs, const int sz) {
    assert(sz <= intof(xs.size()));
    assert(sz >= 2);
    vector<int> ans(sz, 1);

    int record = xs[0] + xs[1];
    int index = 1;

    for (int i = 2; i < sz; ++i) {
        const int candidate = xs[i - 1] + xs[i];

        if (candidate > record) {
            ans[i] = i;
            index = i;
            record = candidate;
        } else {
            ans[i] = index;
        }
    }

    return ans;
}

int best_score(const vector<int> &xs, const int k, const int z) {
    const auto best = best_pair_tails(xs, k + 1);
    const int r_only = accumulate(xs.cbegin(), xs.cbegin() + k + 1, 0);
    int ans = r_only;

    for (int iz = 1; iz <= z && k - 2 * iz >= 0; ++iz) {
        int candidate = r_only;

        for (int j = 0; j < 2 * iz; ++j) {
            assert(k - j >= 0);
            candidate -= xs[k - j];
        }

        assert(k + 1 - 2 * iz > 0);

        candidate += xs[best[k + 1 - 2 * iz] - 1];
        candidate += xs[best[k + 1 - 2 * iz]];

        ans = max(ans, candidate);
    }

    return ans;
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
