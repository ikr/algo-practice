using vi = vector<int>;
using Vert = vector<vi>;
constexpr int flip(const int x) { return x ? 0 : 1; }

struct VertHash final {
    size_t operator()(const Vert &rows) const {
        size_t ans = rows.size() * rows.front().size();

        for (const auto &xs : rows) {
            for (const auto x : xs) {
                ans ^= x + 0x9e3779b9 + (ans << 6) + (ans >> 2);    
            }
        } 

        return ans;
    }
};

vector<vi> flip(Vert rows, const int r, const int c) {
    const int H = rows.size();
    const int W = rows.front().size();

    if (r > 0) { rows[r - 1][c] = flip(rows[r - 1][c]); }
    if (c < W - 1) { rows[r][c + 1] = flip(rows[r][c + 1]); }
    if (r < H - 1) { rows[r + 1][c] = flip(rows[r + 1][c]); }
    if (c > 0) { rows[r][c - 1] = flip(rows[r][c - 1]); }
    
    rows[r][c] = flip(rows[r][c]);
    
    return rows;
}

vector<Vert> adjacent(const Vert &rows) {
    const int H = rows.size();
    const int W = rows.front().size();

    vector<Vert> ans;
    
    for (int r = 0; r != H; ++r) {
        for (int c = 0; c != W; ++c) {
            ans.push_back(flip(rows, r, c));
        }
    }
    
    return ans;
}

bool is_zero(const Vert &rows) {
    for (const auto &row : rows) {
        if (any_of(row.cbegin(), row.cend(), [](const int x) { return x == 1; })) return false;
    }
        
    return true;
}

struct Solution {
    int minFlips(const Vert &rows) const {
        if (is_zero(rows)) return 0;
        
        queue<Vert> q;
        q.push(rows);
        unordered_map<Vert, int, VertHash> dist;
        dist[rows] = 0;
        
        while (!q.empty()) {
            const auto u = q.front();
            q.pop();
            
            for (const auto v : adjacent(u)) {
                if (dist.count(v)) continue;
                if (is_zero(v)) return dist[u] + 1;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
        
        return -1;
    }
};
