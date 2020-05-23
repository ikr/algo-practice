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
    // TODO
    return N;
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
        
        cout << dp << endl;
        
        return area(dp.back().back());
    }
};

// xxxx
// xxxxx
//xxxxxx
//xxxxx
