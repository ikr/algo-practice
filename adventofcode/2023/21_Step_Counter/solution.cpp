#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Coord = pair<int, int>;

static constexpr array Delta{Coord{-1, 0}, Coord{0, 1}, Coord{1, 0},
                             Coord{0, -1}};

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename T> size_t combine_hashes(const T &xs) {
    size_t seed = xs.size();
    for (const auto i : xs) seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        grid.push_back(line);
    }

    Coord src{-1, -1};
    for (int r = 0; r < sz(grid); ++r) {
        for (int c = 0; c < sz(grid[r]); ++c) {
            if (grid[r][c] == 'S') {
                src = {r, c};
                grid[r][c] = '.';
                break;
            }
        }
        if (src.first != -1) break;
    }
    assert(src.first != -1 && src.second != -1);

    const int M = sz(grid);
    assert(sz(grid) == sz(grid[0]));

    const auto inf_grid_at = [&](const Coord p) -> char {
        const auto r = ((p.first % M) + M) % M;
        const auto c = ((p.second % M) + M) % M;
        return grid[r][c];
    };

    const auto adjacent = [&](const Coord p) {
        vector<Coord> ans;
        for (const auto &d : Delta) {
            const auto np = p + d;
            if (inf_grid_at(np) == '#') continue;
            ans.push_back(np);
        }
        return ans;
    };

    const int MaxSteps = 500;
    set<Coord> gen{src};

    const auto tile_digest = [&]() -> size_t {
        vector<int> xs;
        for (int r = 0 - 3 * M; r < M - 3 * M; ++r) {
            for (int c = 0 - 5 * M; c < M - 5 * M; ++c) {
                if (gen.contains({r, c})) xs.push_back(r * M + c);
            }
        }
        return combine_hashes(xs);
    };

    for (int step = 1; step <= MaxSteps; ++step) {
        set<Coord> gen_;

        for (const auto &p : gen) {
            for (const auto &np : adjacent(p)) gen_.insert(np);
        }

        swap(gen, gen_);
        cerr << "step:" << step << " center_digest:" << tile_digest() << endl;
    }
    return 0;
}
