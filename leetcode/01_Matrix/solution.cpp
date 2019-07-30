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

        cache[row][col] = accumulate(candidates.cbegin(), candidates.cend(),
                                     INT_MAX, mmin<int>());
    }

    return cache[row][col];
}

struct Solution {
    VVec updateMatrix(const VVec &rows) { return rows; }
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
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
