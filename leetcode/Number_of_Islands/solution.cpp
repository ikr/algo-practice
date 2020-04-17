#include <bits/stdc++.h>

using namespace std;

using Coord = complex<int>;
constexpr int row(const Coord &coord) { return coord.real(); } 
constexpr int col(const Coord &coord) { return coord.imag(); }

struct CoordHash final {
    size_t operator()(const Coord &coord) const {
        return 31 * hash<int>{}(row(coord)) + hash<int>{}(col(coord));
    }
};

bool operator<(const Coord &lhs, const Coord &rhs) {
    return row(lhs) < row(rhs) || col(lhs) < col(rhs);
}

vector<Coord> adjacent(const vector<vector<char>> &rows, const Coord &coord) {
    vector<Coord> ans{
        coord + Coord{-1, 0}, 
        coord + Coord{0, 1}, 
        coord + Coord{1, 0}, 
        coord + Coord{0, -1}
    };
    
    ans.erase(
        remove_if(ans.begin(), ans.end(), [&rows](const Coord &coord) {
            const int H = rows.size();
            const int W = rows.front().size();
            return coord < Coord{0, 0} || Coord{H - 1, W - 1} < coord || rows[row(coord)][col(coord)] == '0';
        }),
        
        ans.cend()
    );
    
    return ans;
}

struct Solution final {
    int numIslands(const vector<vector<char>> &rows) const {
        const int H = rows.size();
        if (!H) return 0;
        
        const int W = rows.front().size();
        if (!W) return 0;
        
        int ans = 0;
        unordered_set<Coord, CoordHash> discovered;
        
        for (int r = 0; r != H; ++r) {
            for (int c = 0; c != W; ++c) {
                if (rows[r][c] == '0' || discovered.count({r, c})) continue;
                ++ans;
                discovered.emplace(r, c);
                
                queue<Coord> q;
                q.emplace(r, c);
                
                while (!q.empty()) {
                }
            }
        }
        
        return ans;
    }
};

int main() {
    assert(Solution{}.numIslands({
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    }) == 3);
    
    return 0;
}
