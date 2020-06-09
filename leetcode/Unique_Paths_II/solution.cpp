using vi = vector<int>;
using vvi = vector<vi>;

class Solution {
public:
    int uniquePathsWithObstacles(const vvi &rows) {
        const int H = rows.size();
        if (!H) return 0;
        const int W = rows.front().size();
        if (!W) return 0;
        if (rows[0][0] == 1 || rows.back().back() == 1) return 0;

        // number of ways to reach a coord [row r] [column c]
        vvi dp(H, vi(W, 0));
        dp[0][0] = 1;
        for (int c = 1; c < W; ++c) dp[0][c] = rows[0][c] == 1 ? 0 : dp[0][c - 1];
        for (int r = 1; r < H; ++r) dp[r][0] = rows[r][0] == 1 ? 0 : dp[r - 1][0];

        for (int r = 1; r < H; ++r) {
            for (int c = 1; c < W; ++c) {
                if (rows[r][c] == 1) {
                    dp[r][c] == 0;
                    continue;
                }

                dp[r][c] = (dp[r - 1][c] + dp[r][c - 1]);
            }
        }

        return dp.back().back();
    }
};
