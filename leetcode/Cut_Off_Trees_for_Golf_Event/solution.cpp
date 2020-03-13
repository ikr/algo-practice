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
    unordered_set<Coord, CoordHash> discovered{source};
    unordered_map<Coord, int, CoordHash> distance_to{{source, 0}};
    queue<Coord> q;
    q.push(source);

    while (!q.empty()) {
        const Coord v = q.front();
        q.pop();
        if (v == destination) return distance_to[v];

        const auto [first, last] = g.equal_range(v);
        for (auto it = first; it != last; ++it) {
            const Coord u = it->second;
            if (discovered.count(u)) continue;

            discovered.insert(u);
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
        const auto expected = 5637;
        EXPECT(actual == expected);
    },
    CASE("Test case 41 — TLE") {
        vector<vector<int>> input{
{73177,25859,48546,44398,0,43258,97122,89958,10015,20898,64820,87293,17249,6391,49705,11017,90979,60952,8595,52499,55821,0},{1089,45310,0,25522,11362,0,65997,2259,67315,39806,51888,36703,27524,26991,48196,66467,7405,21721,48936,84886,72918,47577},{0,64500,15336,97058,23764,68718,65840,87223,17156,81947,33149,90151,88424,75471,0,33091,93209,45367,69697,14349,0,14183},{42066,55061,81003,32157,81449,21170,43986,80127,85423,97425,89192,78673,85575,27963,53526,0,0,55424,36521,74924,44238,92119},{59096,54148,74036,0,69665,11295,0,0,0,61910,26992,24048,41928,86682,37876,48250,39531,21413,64976,62424,0,48233},{85689,0,49754,9076,21228,51224,84205,96275,0,35346,48224,87861,62431,4241,57760,98843,28525,49052,77358,70132,66935,82242},{11466,80934,74310,84677,61877,75129,65359,93775,12865,63290,37990,0,12680,50002,0,43456,14309,34683,24132,0,82289,89891},{3622,56408,80057,0,82350,20560,37854,30255,0,0,97761,56309,66542,6816,38137,64751,35866,67678,23595,50354,76851,11372},{69273,69541,1786,26045,62434,78292,63356,0,22502,0,20024,0,0,49706,48473,81579,16205,99010,7767,0,19278,0},{52900,51393,20569,56701,86617,3328,21958,35541,9408,96586,71442,77991,30367,79828,32677,77520,8939,44163,65353,70856,37160,0},{15007,0,99863,60594,67689,64017,37552,52164,36250,98960,9336,5598,70343,38631,14176,32508,43555,49304,60871,7533,0,93428},{96502,48246,55050,59744,0,73851,6279,47426,89297,44825,24244,72587,13488,5154,78536,82475,0,93981,33281,23148,77915,95680},{29864,51020,26461,55532,37299,98091,73886,39527,0,86518,6109,36579,28160,70750,95066,50091,65634,17634,93435,18644,10760,79992},{75144,58388,64104,0,87761,12221,55196,91078,9155,78451,94603,10051,0,81834,27440,21653,62758,76840,0,98554,69032,6489},{0,88892,70574,80001,57077,96853,87328,27539,0,11704,85746,26518,64145,80665,16052,97702,45398,63375,33982,8780,0,68822},{30196,77703,43120,91231,0,13660,82584,44346,21788,12088,0,26750,63121,57558,5914,31588,3498,42563,99084,54839,50100,12128},{4329,88151,85682,0,75773,95757,93633,31907,59859,18613,43573,32295,77211,44242,83589,34188,43195,91278,81236,99859,92152,34070},{59625,42542,0,46476,13869,54908,29072,49263,8703,52975,76361,46492,36829,4422,64716,96649,13347,37814,31734,0,6543,87910},{37053,79135,25864,0,83730,48273,55144,77519,7269,91110,54231,51276,6393,30413,46758,12522,31116,0,77695,56285,10640,50523},{37914,38217,36930,89296,7619,0,17711,1391,84998,41261,61701,32114,35860,50653,0,35210,68413,0,39630,21319,0,5258},{67541,65729,52262,96930,97492,59066,92849,73283,24681,75630,19646,67840,93151,54500,0,0,30730,2401,0,30809,0,3977},{1835,62855,84036,0,13505,0,45413,87903,5304,0,11940,85116,82471,0,38332,73992,64721,89529,93285,75514,19384,42518},{59941,25963,8179,96199,0,0,1986,78866,71483,9233,895,28507,62989,12310,21246,26078,33087,43584,91071,22460,72069,85637},{82083,489,24595,15533,46827,87481,26203,97132,48579,15708,4413,98737,0,26482,69928,53828,23619,27525,54343,70491,39804,0}
        };

        const auto actual = Solution{}.cutOffTree(input);
        const auto expected = 7088;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
