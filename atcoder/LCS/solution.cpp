#include <bits/stdc++.h>

using namespace std;

int safe_el(const vector<vector<int>> &rows, const int row, const int col) {
    return (row >= 0 && col >= 0) ? rows[row][col] : 0;
}

string solve(const string &s1, const string &s2) {
    const int sz1 = s1.size();
    const int sz2 = s2.size();
    
    // max-length [up to this index in s1][up to this index in s2]
    vector<vector<int>> dp(sz1, vector<int>(sz2, 0));

    // which cell {row, col} led to the cell [i][j] in dp 
    vector<vector<pair<int, int>>> origins(sz1, vector<pair<int, int>>(sz2, {-1, -1}));
    
    for (int i = 0; i != sz1; ++i) {
        for (int j = 0; j != sz2; ++j) {
            if (s1[i] == s2[j]) {
                dp[i][j] = safe_el(dp, i - 1, j - 1) + 1;
                origins[i][j] = {i - 1, j - 1};
            } else {
                const int a = safe_el(dp, i, j - 1);
                const int b = safe_el(dp, i - 1, j);

                dp[i][j] = max(a, b);
                origins[i][j] = a >= b ? pair<int, int>{i, j - 1} : pair<int, int>{i - 1, j};
            }
        }
    }
    
    vector<pair<int, int>> path{{sz1 - 1, sz2 - 1}};
    auto coord = origins.back().back();
    
    for (;;) {
        path.push_back(coord);
        if (coord.first < 0 || coord.second < 0) break;
        coord = origins[coord.first][coord.second];
    }
    
    reverse(path.begin(), path.end());
    
    string ans;
    
    for (auto i = 1U; i < path.size(); ++i) {
        const auto p = path[i - 1];
        const auto q = path[i];
        
        if (q.first == p.first + 1 && q.second == p.second + 1) {
            ans += s1[q.first];
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    string s1, s2;
    cin >> s1 >> s2;
    cout << solve(s1, s2) << endl;
    
    return 0;
}
