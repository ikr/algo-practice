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

    const auto i0 =
        inof(find_if(cbegin(xs), cend(xs), [](const int x) { return x % 2; }) -
             cbegin(xs));

    reverse(begin(xs), end(xs));
    const auto i1 =
        inof(find_if(cbegin(xs), cend(xs), [](const int x) { return x % 2; }) -
             cbegin(xs));

    if (i1 <= i0) {
        ++xs[i1];
    } else {
        reverse(begin(xs), end(xs));
        ++xs[i0];
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

        cout << num_subarrays_with_at_least_one_one(preprocess(std::move(xs)))
             << '\n';
    }

    return 0;
}
