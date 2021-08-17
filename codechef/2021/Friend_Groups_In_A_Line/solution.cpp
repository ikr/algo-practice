#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi indices_of_ones(const string &xs) {
    vi ans;
    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == '1') {
            ans.push_back(i);
        }
    }
    return ans;
}

static constexpr int INF = 1'000'000'000;

int min_groups(const int k, const vi &xs) {
    if (xs.empty()) return 0;

    vector<array<int, 3>> dp(sz(xs), array{INF, INF, INF});
    dp[0][0] = 1;

    for (int i = 1; i < sz(xs); ++i) {
        for (int d = 0; d <= 2; ++d) {
            if (xs[i] - d < 0) break;

            for (int o = 0; o <= 2; ++o) {
                if (xs[i - 1] - o < 0) break;

                const int challenger = (abs((xs[i] - d) - (xs[i - 1] - o)) <= k)
                                           ? dp[i - 1][o]
                                           : dp[i - 1][o] + 1;
                dp[i][d] = min(dp[i][d], challenger);
            }
        }
    }

    return *min_element(cbegin(dp.back()), cend(dp.back()));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        string xs(n, ' ');
        cin >> xs;

        cout << min_groups(k, indices_of_ones(xs)) << '\n';
    }

    return 0;
}
