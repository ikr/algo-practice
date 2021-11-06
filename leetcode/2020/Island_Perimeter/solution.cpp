int px_perimeter(const vector<vector<int>>& rows, const int r, const int c) {
    const int H = rows.size();
    const int W = rows.front().size();
    int ans = 0;
    
    if (!r || rows[r - 1][c] == 0) ++ans;
    if (c == W - 1 || rows[r][c + 1] == 0) ++ans;
    if (r == H - 1 || rows[r + 1][c] == 0) ++ans;
    if (!c || rows[r][c - 1] == 0) ++ans;
    
    return ans;
}

struct Solution final {
    int islandPerimeter(const vector<vector<int>>& rows) {
        const int H = rows.size();
        if (!H) return 0;
        const int W = rows.front().size();
        if (!W) return 0;       
        int ans = 0;

        for (int r = 0; r != H; ++r) {
            for (int c = 0; c != W; ++c) {
                if (rows[r][c] == 1) ans += px_perimeter(rows, r, c);
            }
        }
        
        return ans;
    }
};
