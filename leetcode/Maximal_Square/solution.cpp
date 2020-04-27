#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    int maximalSquare(const vector<vector<char>> &rows) const {
        const int H = rows.size();
        if (!H) return 0;

        const int W = rows.front().size();
        if (!W) return 0;

        // dp[r][c] -- max size of all squares having (r, c) as bottom-right
        vector<vector<int>> dp(H, vector<int>(W, 0));
        for (int r = 0; r != H; ++r) {
            for (int c = 0; c != W; ++c) {
                const char d = rows[r][c];
                if (d == '0') continue;

                const int sz_N = r > 0 ? dp[r - 1][c] : 0;
                const int sz_W = c > 0 ? dp[r][c - 1] : 0;
                const int sz_NW = r > 0 && c > 0 ? dp[r - 1][c - 1] : 0;

                dp[r][c] = min({sz_N, sz_W, sz_NW}) + 1;
            }
        }

        int sz = 0;
        for (int r = 0; r != H; ++r) {
            for (int c = 0; c != W; ++c) {
                sz = max(sz, dp[r][c]);
            }
        }
        
        return sz * sz;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    const vector<vector<char>> input{
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '1', '1', '1'}
    };

    cout << "ANS " << Solution{}.maximalSquare(input) << endl;

    return 0;
}
