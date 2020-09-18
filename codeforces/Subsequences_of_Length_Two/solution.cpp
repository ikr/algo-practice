#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
constexpr int INF = 1e9;

int max_occurances_one_letter(const int k, const string &s, const char l) {
    const int n = s.size();
    const int ls = count(cbegin(s), cend(s), l);
    const int not_ls = n - ls;
    const int d = min(k, not_ls);

    return (ls + d) * (ls + d - 1) / 2;
}

int max_occurances(const int k, const string &s, const char a, const char b) {
    if (a == b) return max_occurances_one_letter(k, s, a);
    const int n = s.size();

    // The value is -INF if the indices combination is impossible. Otherwise,
    // it's the maximum number of occurances [up to index p] after [r
    // replacements used] when there are [exactly q a-s up to p]
    vector<vvi> dp(n, vvi(k + 1, vi(n + 1, -INF)));

    if (s[0] == a) {
        dp[0][0][1] = 0;
    } else {
        dp[0][0][0] = 0;
        if (k > 0) dp[0][1][1] = 0;
    }

    for (int p = 1; p < n; ++p) {
        for (int r = 0; r <= k; ++r) {
            for (int q = 0; q <= n; ++q) {
                // No change
                const int o1 =
                    (s[p] == b
                         ? dp[p - 1][r][q] + q
                         : (s[p] == a ? (q == 0 ? -INF : dp[p - 1][r][q - 1])
                                      : dp[p - 1][r][q]));

                // Replace with a
                const int o2 =
                    ((q == 0 || r == 0) ? -INF : dp[p - 1][r - 1][q - 1]);

                // Replace with b
                const int o3 = (r == 0 ? -INF : dp[p - 1][r - 1][q] + q);

                dp[p][r][q] = max({o1, o2, o3});
            }
        }
    }

    return accumulate(cbegin(dp.back()), cend(dp.back()), 0,
                      [](const int acc, const vi &xs) {
                          return max(acc, *max_element(cbegin(xs), cend(xs)));
                      });
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    string s(n, ' ');
    cin >> s;

    string t;
    cin >> t;

    cout << max_occurances(k, s, t[0], t[1]) << '\n';
    return 0;
}
