#include <bits/stdc++.h>
using namespace std;
using Cube = tuple<int, int, int>;

bool are_neighs(const Cube &c1, const Cube &c2) {
    const auto [x1, y1, z1] = c1;
    const auto [x2, y2, z2] = c2;
    return max({abs(x1 - x2), abs(y1 - y2), abs(z1 - z2)}) == 1;
}

int count_neighs(const set<Cube> &cubes, const Cube &c) {
    int ans = 0;
    for (const auto &cc : cubes) {
        if (are_neighs(c, cc)) ++ans;
    }
    return ans;
}

set<Cube> all_neighs(const Cube &c) {
    const auto [x, y, z] = c;
    set<Cube> ans;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dz = -1; dz <= 1; ++dz) {
                if (!dx && !dy && !dz) continue;
                ans.emplace(x + dx, y + dy, z + dz);
            }
        }
    }

    return ans;
}

set<Cube> evolve(const set<Cube> &cubes) {
    set<Cube> ans;

    for (const auto &c : cubes) {
        const auto neighs = all_neighs(c);
        ans.insert(cbegin(neighs), cend(neighs));
    }

    for (auto it = ans.begin(); it != ans.end();) {
        const int ns = count_neighs(cubes, *it);

        if (cubes.count(*it)) { // active
            if (ns == 2 || ns == 3) {
                ++it;
            } else {
                it = ans.erase(it);
            }
        } else { // inactive
            if (ns == 3) {
                ++it;
            } else {
                it = ans.erase(it);
            }
        }
    }

    return ans;
}

int solve(set<Cube> cubes) {
    for (int i = 0; i < 6; ++i) {
        cubes = evolve(cubes);
    }

    return cubes.size();
}

int main() {
    set<Cube> cubes;
    for (auto [line, y] = pair{string{}, 0}; getline(cin, line); ++y) {
        const int xsz = line.size();
        for (auto x = 0; x < xsz; ++x) {
            if (line[x] == '#') {
                cubes.emplace(x, y, 0);
            }
        }
    }

    cout << solve(cubes) << '\n';
    return 0;
}
