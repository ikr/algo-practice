#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using vi = vector<int>;
using si = set<int>;
using usi = unordered_set<int>;
using vll = vector<ll>;
using vd = vector<double>;
static const ll M = 1e9 + 7;

double solve(const vd &ps) {
    const int sz = ps.size();
    
    // probability for [i coins] to have [j heads]
    vector<vd> dp(sz + 1, vd(sz + 1, 0.0));
    dp[0][0] = 1.0;
    for (int j = 1; j <= sz; ++j) {
        dp[j][0] = dp[j - 1][0] * (1.0 - ps[j - 1]);
    }
    
    for (int i = 1; i <= sz; ++i) {
        for (int j = 1; j <= sz; ++j) {
            dp[i][j] = dp[i - 1][j] * (1.0 - ps[i - 1]) + dp[i - 1][j - 1] * ps[i - 1];
        }
    }
    
    double ans = 0.0;
    for (int i = sz / 2 + 1; i <= sz; ++i) {
        ans += dp[sz][i];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.precision(17);
    
    int sz;
    cin >> sz;
    vd ps(sz, 0.0);
    for (double &p : ps) cin >> p;

    cout << solve(ps) << endl; 
    return 0;
}
