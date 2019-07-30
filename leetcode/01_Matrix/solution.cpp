#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using Vec = vector<int>;
using VVec = vector<Vec>;
using RowCol = pair<int, int>;

template <typename T> struct mmin {
    constexpr T operator()(const T &a, const T &b) const {
        return std::min(a, b);
    }
};

vector<RowCol> adjacent_nw(const RowCol p) {
    vector<RowCol> ans;
    const auto [row, col] = p;
    if (row > 0) ans.emplace_back(row - 1, col);
    if (col > 0) ans.emplace_back(row, col - 1);
    return ans;
}

vector<RowCol> adjacent_se(const RowCol sz, const RowCol p) {
    vector<RowCol> ans;
    const auto [h, w] = sz;
    const auto [row, col] = p;
    if (row < h - 1) ans.emplace_back(row + 1, col);
    if (col < w - 1) ans.emplace_back(row, col + 1);
    return ans;
}

int min_dist_se(const VVec &rows, VVec &cache, const RowCol p) {
    const auto [row, col] = p;
    if (cache[row][col] != INT_MAX) return cache[row][col];

    if (!rows[row][col]) {
        cache[row][col] = 0;
    } else {
        const auto adj = adjacent_nw(p);
        Vec candidates(adj.size());
        transform(adj.cbegin(), adj.cend(), candidates.begin(),
                  [&rows, &cache](const RowCol a) {
                      return min_dist_se(rows, cache, a);
                  });

        const auto min_neigh = accumulate(
            candidates.cbegin(), candidates.cend(), INT_MAX, mmin<int>());
        cache[row][col] = min_neigh == INT_MAX ? INT_MAX : min_neigh + 1;
    }

    return cache[row][col];
}

int min_dist_nw(const VVec &rows, VVec &cache, const RowCol p) {
    const auto [row, col] = p;
    if (cache[row][col] != INT_MAX) return cache[row][col];

    if (!rows[row][col]) {
        cache[row][col] = 0;
    } else {
        const auto adj = adjacent_se({rows.size(), rows[0].size()}, p);
        Vec candidates(adj.size());
        transform(adj.cbegin(), adj.cend(), candidates.begin(),
                  [&rows, &cache](const RowCol a) {
                      return min_dist_nw(rows, cache, a);
                  });

        const auto min_neigh = accumulate(
            candidates.cbegin(), candidates.cend(), INT_MAX, mmin<int>());
        cache[row][col] = min_neigh == INT_MAX ? INT_MAX : min_neigh + 1;
    }

    return cache[row][col];
}

struct Solution {
    VVec updateMatrix(const VVec &rows) {
        if (rows.empty() || rows[0].empty()) return rows;

        VVec ans(rows.size());

        for (auto &ans_row : ans) {
            ans_row = Vec(rows[0].size(), INT_MAX);
        }

        for (size_t i = 0; i != rows.size(); ++i) {
            for (size_t j = 0; j != rows[i].size(); ++j) {
                ans[i][j] = min_dist_se(rows, ans, {i, j});
            }
        }

        for (size_t i = rows.size() - 1; i-- > 0;) {
            for (size_t j = rows[i].size() - 1; j-- > 0;) {
                ans[i][j] = min_dist_se(rows, ans, {i, j});
            }
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Problem statement example 1") {
        const auto actual = Solution{}.updateMatrix({
                {0,0,0},
                {0,1,0},
                {0,0,0},
            });

        const VVec expected = {
                {0,0,0},
                {0,1,0},
                {0,0,0},
        };

        EXPECT(actual == expected);
    },
    CASE("Problem statement example 2") {
        const auto actual = Solution().updateMatrix({
                {0,0,0},
                {0,1,0},
                {1,1,1},
            });

        const VVec expected = {
                {0,0,0},
                {0,1,0},
                {1,2,1},
       };

        EXPECT(actual == expected);
    },
    CASE("First submission failure") {
        const auto actual = Solution().updateMatrix({{0,1,0,1,1},{1,1,0,0,1},{0,0,0,1,0},{1,0,1,1,1},{1,0,0,0,1}});
        const VVec expected = {{0,1,0,1,2},{1,1,0,0,1},{0,0,0,1,0},{1,0,1,1,1},{1,0,0,0,1}};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
