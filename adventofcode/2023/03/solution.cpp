#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

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

constexpr bool neighs_a_symbol(const vector<string> &grid, const int r0,
                               const int c0) {
    for (const auto dr : {-1, 0, 1}) {
        for (const auto dc : {-1, 0, 1}) {
            if (!dr && !dc) continue;
            const auto r = r0 + dr;
            const auto c = c0 + dc;
            if (!in_bounds(grid, r, c)) continue;
            if (grid[r][c] != '.' && !isdigit(grid[r][c])) return true;
        }
    }
    return false;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) grid.push_back(line);

    int result{};
    for (int r = 0; r < sz(grid); ++r) {
        const auto nums = locate_numbers(grid[r]);
        for (const auto &[c, s] : nums) {
            if (neighs_a_symbol(grid, r, c) ||
                neighs_a_symbol(grid, r, c + sz(s) - 1)) {
                result += stoi(s);
            }
        }
    }

    cout << result << '\n';
    return 0;
}
