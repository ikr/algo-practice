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
    const Graph adjacent;
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
    unordered_set<Coord, CoordHash> visited;
    unordered_map<Coord, int, CoordHash> distance_to{{source, 0}};
    queue<Coord> q;
    q.push(source);

    while (!q.empty()) {
        const Coord v = q.front();
        q.pop();
        if (v == destination) return distance_to[v];

        visited.insert(v);

        const auto [first, last] = g.equal_range(v);
        for (auto it = first; it != last; ++it) {
            const Coord u = it->second;
            if (visited.count(u)) continue;

            distance_to[u] = distance_to[v] + 1;
            q.push(u);
        }
    }

    return -1;
}
} // namespace

struct Solution final {
    int cutOffTree(const vector<vector<int>> &forest) {
        auto [destinations_heap, g] = model(forest);
        int ans = 0;
        Coord source{0, 0};

        while (!destinations_heap.empty()) {
            pop_heap(destinations_heap.begin(), destinations_heap.end(),
                     DestCmp{});
            const auto destination = destinations_heap.back();
            destinations_heap.pop_back();

            const int segment_steps = min_steps(g, source, destination.coord);
            if (segment_steps < 0) return -1;

            ans += segment_steps;
            source = destination.coord;
        }

        return ans;
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
    CASE("Minimal") {
        vector<vector<int>> input{
            {2,1}
        };

        const auto actual = Solution{}.cutOffTree(input);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Arbitrary") {
        vector<vector<int>> input{
            {1,1,1,1,1},
            {0,0,0,0,1},
            {2,0,0,1,1},
            {3,1,1,1,1},
            {1,1,1,1,1},
            {1,1,1,1,1},
        };

        const auto actual = Solution{}.cutOffTree(input);
        const auto expected = 13;
        EXPECT(actual == expected);
    },
    CASE("Test case 34 — TLE") {
        vector<vector<int>> input{
            {69438,55243,0,43779,5241,93591,73380},
            {847,49990,53242,21837,89404,63929,48214},
            {90332,49751,0,3088,16374,70121,25385},
            {14694,4338,87873,86281,5204,84169,5024},
            {31711,47313,1885,28332,11646,42583,31460},
            {59845,94855,29286,53221,9803,41305,60749},
            {95077,50343,27947,92852,0,0,19731},
            {86158,63553,56822,90251,0,23826,17478},
            {60387,23279,78048,78835,5310,99720,0},
            {74799,48845,60658,29773,96129,90443,14391},
            {65448,63358,78089,93914,7931,68804,72633},
            {93431,90868,55280,30860,59354,62083,47669},
            {81064,93220,22386,22341,95485,20696,13436},
            {50083,0,89399,43882,0,13593,27847},
            {0,12256,33652,69301,73395,93440,0},
            {42818,87197,81249,33936,7027,5744,64710},
            {35843,0,99746,52442,17494,49407,63016},
            {86042,44524,0,0,26787,97651,28572},
            {54183,83466,96754,89861,84143,13413,72921},
            {89405,52305,39907,27366,14603,0,14104},
            {70909,61104,70236,30365,0,30944,98378},
            {20124,87188,6515,98319,78146,99325,88919},
            {89669,0,64218,85795,2449,48939,12869},
            {93539,28909,90973,77642,0,72170,98359},
            {88628,16422,80512,0,38651,50854,55768},
            {13639,2889,74835,80416,26051,78859,25721},
            {90182,23154,16586,0,27459,3272,84893},
            {2480,33654,87321,93272,93079,0,38394},
            {34676,72427,95024,12240,72012,0,57763},
            {97957,56,83817,45472,0,24087,90245},
            {32056,0,92049,21380,4980,38458,3490},
            {21509,76628,0,90430,10113,76264,45840},
            {97192,58807,74165,65921,45726,47265,56084},
            {16276,27751,37985,47944,54895,80706,2372},
            {28438,53073,0,67255,38416,63354,69262},
            {23926,75497,91347,58436,73946,39565,10841},
            {34372,69647,44093,62680,32424,69858,68719},
            {24425,4014,94871,1031,99852,88692,31503},
            {24475,12295,33326,37771,37883,74568,25163},
            {0,18411,88185,60924,29028,69789,0},
            {34697,75631,7636,16190,60178,39082,7052},
            {24876,9570,53630,98605,22331,79320,88317},
            {27204,89103,15221,91346,35428,94251,62745},
            {26636,28759,12998,58412,38113,14678,0},
            {80871,79706,45325,3861,12504,0,4872},
            {79662,15626,995,80546,64775,0,68820},
            {25160,82123,81706,21494,92958,33594,5243},
        };

        const auto actual = Solution{}.cutOffTree(input);
        const auto expected = -1;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
