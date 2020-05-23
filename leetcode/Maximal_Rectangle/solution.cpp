using vc = vector<char>;
using Dim = pair<int, int>;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

constexpr Dim operator+(const Dim &lhs, const Dim &rhs) {
    const auto [a, b] = lhs;
    const auto [c, d] = rhs;
    return {a + c, b + d};
}

constexpr int area(const Dim &dim) {
    return dim.first * dim.second;
}

Dim largest_at_bottom_rigth(const Dim N, const Dim W, const Dim NW) {
    vector<Dim> candidates{{1, 1}};
    if (N.first) candidates.emplace_back(N.first + 1, 1);
    if (W.second) candidates.emplace_back(1, W.second + 1);
    
    if (N.second > 1 && W.first > 1) {
        const Dim overlap_n_w{min(W.first, N.first + 1), min(W.second + 1, N.second)};
        candidates.push_back(overlap_n_w);
        
        //if (NW.first + 1 >= overlap_n_w.first)
    }
    
    return *max_element(candidates.cbegin(), candidates.cend(), [](const Dim &lhs, const Dim &rhs) {
        return area(lhs) < area(rhs);
    });
}

int max_area(const vector<vector<Dim>> &dp) {
    int ans = 0;
    for (int r = 0; r != dp.size(); ++r) {
        for (int c = 0; c != dp[0].size(); ++c) ans = max(ans, area(dp[r][c]));
    }
    return ans;
}

struct Solution final {
    int maximalRectangle(const vector<vc> &rows) const {
        const int H = rows.size();
        if (!H) return 0;
        const int W = rows[0].size();
        if (!W) return 0;
        
        // largest by are having its bottom-right at [row i] [column j]
        vector<vector<Dim>> dp(H, vector<Dim>(W, {0, 0}));
        if (rows[0][0] == '1') dp[0][0] = {1, 1};
        
        for (int c = 1; c != W; ++c) {
            if (rows[0][c] == '1') {
                dp[0][c] = dp[0][c - 1] + Dim{0, 1};
            }
        }
        
        for (int r = 1; r != H; ++r) {
            if (rows[r][0] == '1') {
                dp[r][0] = dp[r - 1][0] + Dim{1, 0};
            }
        }
        
        for (int r = 1; r != H; ++r) {
            for (int c = 1; c != W; ++c) {
                if (rows[r][c] == '0') continue;
                dp[r][c] = largest_at_bottom_rigth(dp[r - 1][c], dp[r][c - 1], dp[r - 1][c - 1]);
            }
        }
        
        cout << dp << endl;
        
        return max_area(dp);
    }
};

// xxxx
// xxxxx
//xxxxxx
//xxxxx
