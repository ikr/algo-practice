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

bool in_bounds(const vector<vi> &rows, const Coord &coord) {
    const int H = rows.size();
    const int W = rows[0].size();
    return row(coord) >= 0 && row(coord) < H && col(coord) >= 0 && col(coord) < W; 
}

void counting_dfs(int &ans, const Model &model, State &state) {
    if (
        !in_bounds(model.rows, state.curr) || 
        state.path.count(state.curr) || 
        model.rows[row(state.curr)][col(state.curr)] == -1
    ) return;
    
    if (state.curr == model.dest && state.path.size() == model.target_path_size) {
        ++ans;
        return;
    }
    
    const Coord stash = state.curr;
    for (const auto delta : {Coord{-1, 0}, Coord{0, 1}, Coord{1, 0}, Coord{0, -1}}) {
        state.curr = state.curr + delta;
        state.path.insert(state.curr);
        
        counting_dfs(ans, model, state);
        
        state.path.erase(state.curr);
        state.curr = stash;
    }
}

struct Solution {
    int uniquePathsIII(const vector<vi> &rows) const {
        auto [model, state] = initial_model_state(rows);
        
        int ans = 0;
        counting_dfs(ans, model, state);
        return ans;
    }
};
