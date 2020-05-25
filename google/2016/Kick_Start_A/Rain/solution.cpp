#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pi = pair<int, int>;

template <typename T1, typename T2> struct PairHash final {
    size_t operator()(const pair<T1, T2> &p) const {
        return 31 * hash<T1>{}(p.first) + hash<T2>{}(p.second);
    }
};

using uspi = unordered_set<pi, PairHash<int, int>>;

template <typename T> constexpr pair<T, T> operator+(const pair<T, T> &lhs, const pair<T, T> &rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

bool in_bounds(const vvi &rows, const pi coord) {
    const int H = rows.size();
    const int W = rows[0].size();
    const auto r = coord.first;
    const auto c = coord.second;    
    return (0 <= r && r < H && 0 <= c && c < W);
}

bool is_on_slope(const vvi &rows, const pi coord) {
    const int H = rows.size();
    const int W = rows[0].size();
    
    uspi discovered{coord};
    stack<pi> s;
    s.push(coord);
        
    while (!s.empty()) {
        const auto r = s.top().first;
        const auto c = s.top().second;
        s.pop();
        if (r == 0 || r == H - 1 || c == 0 || c == W - 1) return true;
        
        for (const auto delta : {pi{-1, 0}, pi{0, 1}, pi{1, 0}, pi{0, -1}}) {
            const auto adj = pi{r, c} + delta;
            
            if (
                in_bounds(rows, adj) && 
                rows[adj.first][adj.second] <= rows[coord.first][coord.second] &&
                !discovered.count(adj)
            ) {
                s.push(adj);
                discovered.insert(adj);
            }
        }
    }
    
    return false;
}

uspi discover_slopes(const vvi &rows) {
    const int H = rows.size();
    const int W = rows[0].size();
    
    uspi ans;
    for (int r = 0; r != H; ++r) {
        for (int c = 0; c != W; ++c) {
            if (is_on_slope(rows, {r, c})) ans.emplace(r, c);
        }
    }
    return ans;
}

int discover_edge_height(const vvi &rows, const uspi &slopes, const pi coord) {
    int ans = INT_MAX;
    uspi discovered{coord};
    stack<pi> s;
    s.push(coord);
    
    while (!s.empty()) {
        const auto r = s.top().first;
        const auto c = s.top().second;
        s.pop();
        
        if (slopes.count({r, c})) {
            ans = min(ans, rows[r][c]);
        } else {
            for (const auto delta : {pi{-1, 0}, pi{0, 1}, pi{1, 0}, pi{0, -1}}) {
                const auto adj = pi{r, c} + delta;

                if (in_bounds(rows, adj) && !discovered.count(adj)) {
                    s.push(adj);
                    discovered.insert(adj);
                }
            }
        }
    }
    
    return ans;
}

int solve (const vvi &rows) {
    const auto slopes = discover_slopes(rows);
    const int H = rows.size();
    const int W = rows[0].size();
    
    int ans = 0;
    for (int r = 0; r != H; ++r) {
        for (int c = 0; c != W; ++c) {
            if (slopes.count({r, c})) continue;
            ans += discover_edge_height(rows, slopes, {r, c}) - rows[r][c];
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        int R, C;
        cin >> R >> C;
        vvi rows(R, vi(C, 0));
        
        for (auto &row : rows) {
            for (auto &x : row) cin >> x;
        }
        
        cout << "Case #" << i << ": " << solve(rows) << '\n';
    }

    return 0;
}
