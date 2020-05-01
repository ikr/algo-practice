#include <bits/stdc++.h>

using namespace std;

string longest(const string &s1, const string &s2) {
    return s1.size() >= s2.size() ? s1 : s2;
}

string safe_el(const vector<vector<string>> &rows, const int row, const int col) {
    return (row >= 0 && col >= 0) ? rows[row][col] : "";
}

string solve(const string &s1, const string &s2) {
    const int sz1 = s1.size();
    const int sz2 = s2.size();
    
    // answer [up to this index in s1][up to this index in s2]
    vector<vector<string>> dp(sz1, vector<string>(sz2, ""));
    
    for (int i = 0; i != sz1; ++i) {
        for (int j = 0; j != sz2; ++j) {
            if (s1[i] == s2[j]) {
                dp[i][j] = safe_el(dp, i - 1, j - 1) + s1[i];
            } else {
                dp[i][j] = longest(safe_el(dp, i, j - 1), safe_el(dp, i - 1, j));
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
    cout << solve(s1, s2) << endl;
    
    return 0;
}
