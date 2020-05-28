#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
 
int max_digit(int x) {
    int ans = 0;
    while (x) {
        ans = max(ans, x % 10);
        x /= 10;
    }
    return ans;
}
 
int solve(const int x) {
    vi dp(x + 1, 1);
    dp[0] = 0;
 
    for (int i = 10; i <= x; ++i) {
        dp[i] = dp[i - max_digit(i)] + 1;
    }
    return dp.back();
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int x;
    cin >> x;
    cout << solve(x) << '\n';
    return 0;
}
