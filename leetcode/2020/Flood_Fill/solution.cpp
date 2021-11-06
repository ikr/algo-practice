using vi = vector<int>;
using pii = pair<int, int>;

template <typename T1, typename T2> struct PairHash final {
    size_t operator()(const pair<T1, T2> &p) const {
        return 31 * hash<T1>{}(p.first) + hash<T2>{}(p.second);
    }
};

pii operator+(const pii lhs, const pii rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

bool in_bounds(const vector<vi> &rows, const pii coord) {
    const int H = rows.size();
    const int W = rows.front().size();
    const auto [r, c] = coord;
    return r >= 0 && c >= 0 && r < H && c < W; 
}

struct Solution final {
    vector<vi> floodFill(vector<vi> &rows, const int sr, const int sc, const int new_color) {
        if (rows.empty() || rows.front().empty()) return rows;
        
        const int old_color = rows[sr][sc];
        rows[sr][sc] = new_color;
        queue<pii> q;
        q.emplace(sr, sc);
        unordered_set<pii, PairHash<int, int>> discovered{{sr, sc}};
        
        while (!q.empty()) {
            const auto u = q.front();
            q.pop();
            
            for (const pii v : {u + pii{-1, 0}, u + pii{0, 1}, u + pii{1, 0}, u + pii{0, -1}}) {
                const auto [r, c] = v;
                if (!in_bounds(rows, v) || rows[r][c] != old_color || discovered.count(v)) continue;
                
                rows[r][c] = new_color;
                discovered.emplace(r, c);
                q.emplace(r, c);
            }
        }
        
        return rows;
    }
};
