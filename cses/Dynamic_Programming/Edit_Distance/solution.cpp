#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

int edit_distance(const string &s1, const string &s2) {
    const int sz1 = s1.size();
    const int sz2 = s2.size();
    
    // answer [up to s1 prefix of lenght i] [up to s2 prefix of length j]
    vvi dp(sz1 + 1, vi(sz2 + 1, 0));
    
    for (int i = 1; i <= sz1; ++i) dp[i][0] = i;
    for (int j = 1; j <= sz2; ++j) dp[0][j] = j;
    
    for (int i = 1; i <= sz1; ++i) {
        for (int j = 1; j <= sz2; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
            }
        }
    }
    
    return dp.back().back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s1, s2;
    cin >> s1 >> s2;

    cout << edit_distance(s1, s2) << '\n';
    
    return 0;
}
