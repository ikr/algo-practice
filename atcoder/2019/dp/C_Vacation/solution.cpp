#include <bits/stdc++.h>

using namespace std;

using Opts = array<int, 3>;

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);
    
    int sz;
    cin >> sz;
    
    vector<Opts> dp(sz, {INT_MIN, INT_MIN, INT_MIN});
    
    for (int i = 0; i != sz; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        
        if (i == 0) {
            dp[i] = {a, b, c};
        } else {
            dp[i][0] = a + max(dp[i - 1][1], dp[i - 1][2]);
            dp[i][1] = b + max(dp[i - 1][0], dp[i - 1][2]);        
            dp[i][2] = c + max(dp[i - 1][0], dp[i - 1][1]);    
        }
    }
    
    cout << *max_element(dp.back().cbegin(), dp.back().cend()) << endl;
    
    return 0;
}
