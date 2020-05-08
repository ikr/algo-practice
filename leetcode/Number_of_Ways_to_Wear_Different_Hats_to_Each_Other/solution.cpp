using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

static const ll M = 1e9 + 7;
static const int MAX_HAT = 40;

vector<vi> people_by_hat(const vector<vi> &hats_by_person) {
    const int sz = hats_by_person.size();
    vector<vi> ans(MAX_HAT + 1, vi{});
    
    for (int i = 0; i != sz; ++i) {
        for (const int h : hats_by_person[i]) ans[h].push_back(i);
    }
    
    return ans;
}

int solve(const int n, const vector<vi> &pbh) {
    // count [hat i] [people bits combo j]
    vector<vll> dp(MAX_HAT + 1, vll(1 << n, 0));
    dp[0][0] = 1;
    
    for (int i = 1; i <= MAX_HAT; ++i) {
        for (int j = 0; j < (1 << n); ++j) {
            dp[i][j] += dp[i - 1][j];
            dp[i][j] %= M;
            
            for (const int p : pbh[i]) {
                if ((j & (1 << p)) == 0) {
                    const int jj = j | (1 << p);
                    dp[i][jj] += dp[i - 1][j];
                    dp[i][jj] %= M;
                }
            }
        }
    }
    
    return dp.back().back();
}

struct Solution final {
    int numberWays(const vector<vi> &hbp) const {
        return solve(hbp.size(), people_by_hat(hbp));
    }
};
