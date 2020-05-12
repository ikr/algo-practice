using vi = vector<int>;

using Coord = complex<int>;
constexpr int row(const Coord &coord) { return coord.real(); } 
constexpr int col(const Coord &coord) { return coord.imag(); }

struct CoordHash final {
    size_t operator()(const Coord &coord) const {
        return 31 * hash<int>{}(row(coord)) + hash<int>{}(col(coord));
    }
};

struct Model {
    const vector<vi> rows;
    const Coord dest;
    const int target_path_size;
};

struct State {
    unordered_set<Coord, CoordHash> path;
    Coord curr;
};

pair<Model, State> initial_model_state(const vector<vi> &rows) {
    const int H = rows.size();
    const int W = rows[0].size();
    
    Coord dest = {-1, -1};
    Coord curr = {-1, -1};
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
    
    return {{rows, dest, target_path_size}, {{curr}, curr}};
}

void counting_dfs(int &ans, const Model &model, State &state) {
    
}

struct Solution {
    int uniquePathsIII(const vector<vi> &rows) const {
        return 0;
    }
};
