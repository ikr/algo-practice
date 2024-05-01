#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> preprocess(vector<int> xs) {
    if (all_of(cbegin(xs), cend(xs), [](const int x) { return x % 2 == 0; })) {
        return xs;
    }

    const auto n = sz(xs);
    for (int i = n / 2; i < n; ++i) {
        if (xs[i] % 2) {
            ++xs[i];
            break;
        }
    }

    for (auto &x : xs) {
        if (x % 2) {
            x = 0;
        } else {
            x = 1;
        }
    }
    return xs;
}

ll num_subarrays_with_at_least_one_one(const vector<int> &xs) {
    vector<ll> dp(sz(xs), xs[0]);
    for (int i = 1; i < sz(dp); ++i) {
        if (xs[i]) {
            dp[i] = i + 1;
        } else {
            dp[i] = dp[i - 1];
        }
    }
    return accumulate(cbegin(dp), cend(dp), 0LL);
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

        const auto o1 = num_subarrays_with_at_least_one_one(preprocess(xs));
        reverse(begin(xs), end(xs));
        xs = preprocess(std::move(xs));
        reverse(begin(xs), end(xs));
        const auto o2 = num_subarrays_with_at_least_one_one(xs);

        cout << max(o1, o2) << '\n';
    }

    return 0;
}
