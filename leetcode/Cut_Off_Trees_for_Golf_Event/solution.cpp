#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

namespace {
template <typename T> int intof(const T x) { return static_cast<int>(x); }
using Coord = complex<int>;
int row(const Coord &coord) { return coord.real(); }
int col(const Coord &coord) { return coord.imag(); }

struct Dest final {
    int priority;
    Coord coord;

    Dest(const int p, const int r, const int c) : priority{p}, coord{r, c} {}
};

struct DestCmp final {
    bool operator()(const Dest &lhs, const Dest &rhs) const {
        return lhs.priority < rhs.priority;
    }
};

struct CoordHash final {
    size_t operator()(const Coord &coord) const {
        return 31 * hash<int>{}(row(coord)) + hash<int>{}(col(coord));
    }
};

using Graph = unordered_multimap<Coord, Coord, CoordHash>;

struct Model final {
    vector<Dest> destinations_heap;
    Graph adjacent;
};

Model model(const vector<vector<int>> &forest) {
    vector<Dest> destinations_heap;
    Graph adjacent;

    for (int r = 0; r != intof(forest.size()); ++r) {
        for (int c = 0; c != intof(forest[r].size()); ++c) {
            if (!forest[r][c]) continue;

            if (forest[r][c] > 1) {
                destinations_heap.emplace_back(-forest[r][c], intof(r),
                                               intof(c));

                push_heap(destinations_heap.begin(), destinations_heap.end(),
                          DestCmp{});
            }

            for (const Coord delta :
                 vector<Coord>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
                const Coord neigh = Coord{r, c} + delta;

                if (row(neigh) >= 0 && row(neigh) < intof(forest.size()) &&
                    col(neigh) >= 0 && col(neigh) < intof(forest[r].size()) &&
                    forest[row(neigh)][col(neigh)]) {
                    adjacent.emplace(Coord{r, c}, neigh);
                }
            }
        }
    }

    return {destinations_heap, adjacent};
}

int min_steps(const Graph &g, const Coord &source, const Coord &destination) {
    // TODO
    return 0;
}
} // namespace

struct Solution final {
    int cutOffTree(const vector<vector<int>> &forest) { return forest.size(); }
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
