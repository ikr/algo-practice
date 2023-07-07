#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;

static constexpr int Inf = 1000 * 1000 * 1000;

static const auto InitialWalls = []() -> unordered_set<char> {
    unordered_set<char> ans{'#'};
    for (char c = 'A'; c <= 'Z'; ++c) ans.insert(c);
    return ans;
}();

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

struct Model final {
    vector<string> grid;
    unordered_map<char, Coord> locations;
    unordered_set<char> walls;
};

int distance(const Model &m, const char source, const char destination) {
    const auto [sro, sco] = m.locations.at(source);
    const auto [dro, dco] = m.locations.at(destination);

    const auto H = sz(m.grid);
    const auto W = sz(m.grid[0]);

    vector<vector<int>> D(H, vector(W, Inf));
    D[sro][sco] = 0;

    queue<Coord> q;
    q.push({sro, sco});

    while (!q.empty()) {
        const auto [ro, co] = q.front();
        q.pop();

        for (const auto &[ro_, co_] : vector<Coord>{
                 {ro - 1, co}, {ro, co + 1}, {ro + 1, co}, {ro, co - 1}}) {
            if (D[ro_][co_] != Inf || m.walls.count(m.grid[ro_][co_])) continue;

            D[ro_][co_] = D[ro][co] + 1;
            q.push({ro_, co_});
        }
    }

    return D[dro][dco];
}

int min_total_distance_collecting_all_keys(
    const vector<string> &grid, const unordered_map<char, Coord> &locations) {
    const Model m{grid, locations, InitialWalls};
    cerr << "@ → a: " << distance(m, '@', 'a')
         << ", @ → b: " << distance(m, '@', 'b') << endl;
    return -1;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) grid.push_back(line);

    unordered_map<char, Coord> locations;
    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[ro]); ++co) {
            const auto x = grid[ro][co];
            if (x == '.' || x == '#') continue;
            locations[x] = {ro, co};
        }
    }

    cout << min_total_distance_collecting_all_keys(grid, locations) << '\n';
    return 0;
}
