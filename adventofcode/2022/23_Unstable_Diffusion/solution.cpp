#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        if (line != "") grid.push_back(line);
    }

    set<Coord> elves;
    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[ro]); ++co) {
            if (grid[ro][co] == '#') elves.emplace(ro, co);
        }
    }

    return 0;
}
