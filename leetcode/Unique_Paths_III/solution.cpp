using vi = vector<int>;

using Coord = complex<int>;
constexpr int row(const Coord &coord) { return coord.real(); } 
constexpr int col(const Coord &coord) { return coord.imag(); }

struct CoordHash final {
    size_t operator()(const Coord &coord) const {
        return 31 * hash<int>{}(row(coord)) + hash<int>{}(col(coord));
    }
};

struct State {
    const vector<vi> rows;
    const Coord dest;
    const int target_path_size;
    unordered_set<Coord, CoordHash> path;
    Coord curr;
};

State initial_state(const vector<vi> &rows) {
    const int H = rows.size();
    const int W = rows[0].size();
    
    Coord dest;
    Coord curr;
    int target_path_size = 2;
    
    for (int r = 0; r != H; ++r) {
        for (int c = 0; c != W; ++c) {
            switch (rows[r][c]) {
                case 1:
                    curr = {r, c};
                    break;
                case 2:
                    dest = {r, c};
                    break;  
                case 0:
                    ++target_path_size;
                    break;
            }
        }
    }
    
    return {rows, dest, target_path_size, {}, curr};
}

struct Solution {
    int uniquePathsIII(const vector<vi> &rows) const {
        return 0;
    }
};
