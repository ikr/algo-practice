#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

namespace {
template <typename T> int intof(const T x) { return static_cast<int>(x); }
using RowCol = complex<int>;
int row(const RowCol &coord) { return coord.real(); }
int col(const RowCol &coord) { return coord.imag(); }

struct Dest final {
    int height;
    RowCol coord;
};

struct DestCmp final {
    bool operator()(const Dest &lhs, const Dest &rhs) const {
        return lhs.height < rhs.height;
    }
};
} // namespace

struct Solution final {
    int cutOffTree(vector<vector<int>> &forest) {
        set<Dest, DestCmp> destinations;

        for (auto r = 0U; r != forest.size(); ++r) {
            for (auto c = 0U; c != forest[r].size(); ++c) {
                destinations.insert(
                    Dest{forest[r][c], RowCol{intof(r), intof(c)}});
            }
        }

        return forest.size();
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 1") {
        vector<vector<int>> input{
            {1,2,3},
            {0,0,4},
            {7,6,5}
        };

        const auto actual = Solution{}.cutOffTree(input);
        const auto expected = 6;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        vector<vector<int>> input{
            {1,2,3},
            {0,0,0},
            {7,6,5}
        };

        const auto actual = Solution{}.cutOffTree(input);
        const auto expected = -1;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        vector<vector<int>> input{
            {2,3,4},
            {0,0,5},
            {8,7,6}
        };

        const auto actual = Solution{}.cutOffTree(input);
        const auto expected = 6;
        EXPECT(actual == expected);
    },
    CASE("A single tree") {
        vector<vector<int>> input{
            {1,1,1},
            {0,1,1},
            {2,1,0}
        };

        const auto actual = Solution{}.cutOffTree(input);
        const auto expected = 4;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
