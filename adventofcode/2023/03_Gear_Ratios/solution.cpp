#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pair<int, string>> locate_numbers(const string &row) {
    vector<pair<int, string>> result;

    for (int i = 0; i < sz(row);) {
        if (isdigit(row[i])) {
            string cur{row[i]};
            for (int j = i + 1; j < sz(row) && isdigit(row[j]); ++j) {
                cur += row[j];
            }

            result.emplace_back(i, cur);
            i += sz(cur);
        } else {
            ++i;
        }
    }

    return result;
}

constexpr bool in_bounds(const vector<string> &grid, const int r0,
                         const int c0) {
    return 0 <= r0 && r0 < sz(grid) && 0 <= c0 && c0 < sz(grid[r0]);
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) grid.push_back(line);

    map<pair<int, int>, string> idx;
    map<pair<int, int>, pair<int, int>> num_coords;

    for (int r = 0; r < sz(grid); ++r) {
        const auto nums = locate_numbers(grid[r]);
        for (const auto &[c, s] : nums) {
            idx.emplace(pair{r, c}, s);
            num_coords.emplace(pair{r, c}, pair{r, c});
            num_coords.emplace(pair{r, c + sz(s) - 1}, pair{r, c});
        }
    }

    const auto adjacent_nums = [&](const int r0,
                                   const int c0) -> set<pair<int, int>> {
        set<pair<int, int>> result;
        for (const auto dr : {-1, 0, 1}) {
            for (const auto dc : {-1, 0, 1}) {
                if (!dr && !dc) continue;
                const auto r = r0 + dr;
                const auto c = c0 + dc;
                if (!in_bounds(grid, r, c)) continue;

                const auto it = num_coords.find(pair{r, c});
                if (it == cend(num_coords)) continue;
                result.insert(it->second);
            }
        }
        return result;
    };

    int result{};

    for (int r = 0; r < sz(grid); ++r) {
        for (int c = 0; c < sz(grid[r]); ++c) {
            if (grid[r][c] != '*') continue;
            const auto an = adjacent_nums(r, c);
            if (sz(an) != 2) continue;

            const auto x = stoi(idx.at(*cbegin(an)));
            const auto y = stoi(idx.at(*crbegin(an)));
            result += x * y;
        }
    }

    cout << result << '\n';
    return 0;
}
