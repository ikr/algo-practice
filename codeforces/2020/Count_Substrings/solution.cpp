#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll count_intervals(const string &s, const string &t) {
    const int n = s.size();
    const char a = t[0];
    const char b = t[1];

    // Count of intervals ending at [i]
    vector<ll> dp(n, 0);
    int last_b = -1;

    for (int i = 1; i < n; ++i) {
        const char x = s[i - 1];
        const char y = s[i];

        dp[i] = dp[i - 1];

        if (x == a && y == b) {
            dp[i] += last_b == -1 ? i : i - last_b;
            last_b = i;
        }
    }

    return accumulate(cbegin(dp), cend(dp), 0LL, plus<ll>{});
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    string s(n, ' ');
    cin >> s;
    string t;
    cin >> t;

    cout << count_intervals(s, t) << '\n';

    return 0;
}
