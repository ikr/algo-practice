using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using vi = vector<int>;
using vui = vector<int>;
using vll = vector<ll>;

static const ll M = 1e9 + 7;
static const ui MAX_HAT = 40;
static const ui MAX_PERSON = 9;
static const ui MAX_COMBO = (1 << 10) - 1;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';

    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }

    os << ']';
    return os;
}

int combo(const vi &xs) {
    int ans = 0;
    
    for (const int x : xs) {
        ans |= (1 << x);    
    }
    
    return ans;
}

vector<vi> people_by_hat(const vector<vi> &hats_by_person) {
    const int sz = hats_by_person.size();
    vector<vi> ans(MAX_HAT + 1, vi{});
    int max_hat_seen = 0;
    
    for (int i = 0; i != sz; ++i) {
        for (const int h : hats_by_person[i]) {
            ans[h].push_back(i);
            if (h > max_hat_seen) max_hat_seen = h;
        }
    }
    
    assert(max_hat_seen <= MAX_HAT);
    ans.resize(max_hat_seen + 1);
    
    return ans;
}

int solve(const int people_count, const vector<vi> &pbh) {
    const int sz = pbh.size();
    
    // count [hat i] [people bits combo j]
    vector<vll> dp(sz, vll(1 << people_count, 0));
    
    for (const int p : pbh[1]) {
        dp[1][1 << p] = 1;
    }
    
    for (int i = 2; i < sz; ++i) {
        for (int j = 1; j < (1 << people_count); ++j) {
            if (!dp[i - 1][j]) continue;
            
            for (const int p : pbh[i]) {
                cout << "1 << p " << (1 << p) << ", j " << j << ", j & (1 << p) " << (j & (1 << p)) << endl;
                if ((j & (1 << p)) == 0) {
                    const int jj = j | (1 << p);
                    cout << "jj " << jj << endl;
                    dp[i][jj] = (dp[i][jj] + dp[i - 1][j]) % M; 
                }
            }
        }
    }
    
    for (const auto &row : dp) {
        cout << row << endl;
    }
    
    return dp.back().back();
}

struct Solution final {
    int numberWays(const vector<vi> &hbp) const {
        return solve(hbp.size(), people_by_hat(hbp));
    }
};
