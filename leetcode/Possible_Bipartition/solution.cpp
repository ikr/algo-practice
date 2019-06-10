#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using Vertex = int;
using Group = unordered_set<Vertex>;
using DislikeGraph = unordered_multimap<Vertex, Vertex>;

bool two_coloring_dfs(const DislikeGraph &dg, vector<bool> &colors,
                      Group &visited, const Vertex v) {
    const auto adj_range = dg.equal_range(v);

    for (auto i = adj_range.first; i != adj_range.second; ++i) {
        const Vertex a = i->second;

        if (!visited.count(a)) {
            visited.insert(a);
            colors[a] = !colors[v];
            if (!two_coloring_dfs(dg, colors, visited, a)) return false;
        } else if (colors[v] == colors[a])
            return false;
    }

    return true;
}

struct Solution final {
    bool possibleBipartition(const int sz,
                             const vector<vector<int>> &dislikes) const {
        DislikeGraph dg;

        for (const auto &dl : dislikes) {
            dg.insert(make_pair(dl[0], dl[1]));
            dg.insert(make_pair(dl[1], dl[0]));
        }

        vector<bool> colors(sz + 1);
        Group visited;
        for (Vertex v = 1; v != sz + 1; ++v) {
            if (visited.count(v)) continue;
            visited.insert(v);
            if (!two_coloring_dfs(dg, colors, visited, v)) return false;
        }

        return true;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("problem statement example 1") {
        vector<vector<int>> input{{1,2},{1,3},{2,4}};
        const auto actual = Solution().possibleBipartition(4, input);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("problem statement example 2") {
        vector<vector<int>> input{{1,2},{1,3},{2,3}};
        const auto actual = Solution().possibleBipartition(3, input);
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("problem statement example 3") {
        vector<vector<int>> input{{1,2},{2,3},{3,4},{4,5},{1,5}};
        const auto actual = Solution().possibleBipartition(5, input);
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("my test 1") {
        vector<vector<int>> input{{1,2}};
        const auto actual = Solution().possibleBipartition(9, input);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("my test 2") {
        vector<vector<int>> input{{1,2},{3,4},{5,6}};
        const auto actual = Solution().possibleBipartition(9, input);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("my test 3") {
        vector<vector<int>> input{{2,3},{3,2}};
        const auto actual = Solution().possibleBipartition(9, input);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("my test 4") {
        vector<vector<int>> input{{2,3},{3,4},{4,5},{5,6},{6,2}};
        const auto actual = Solution().possibleBipartition(9, input);
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("trivial") {
        vector<vector<int>> input{};
        const auto actual = Solution().possibleBipartition(9, input);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("submission test 34") {
        vector<vector<int>> input{{26,47},{24,30},{10,17},{25,31},{15,20},{20,42},{21,28},{26,28},{23,41},{31,44},{7,34},{14,46},{11,47},{25,43},{38,40},{44,45},{26,32},{39,45},{10,18},{25,26},{23,35},{22,41},{21,31},{44,50},{33,39},{7,28},{27,36},{35,36},{30,41},{17,36},{16,44},{12,34},{13,35},{27,50},{21,40},{2,32},{39,48},{22,35},{36,48},{12,22},{7,35},{24,49},{37,44},{18,36},{24,36},{7,33},{26,43},{47,50},{2,37},{48,50},{1,21},{22,23},{30,32},{29,40},{17,29},{14,50},{37,47},{24,33},{38,44},{4,31},{31,45},{26,44},{40,41},{29,49},{21,27},{8,32},{7,24},{40,42},{12,24},{41,45},{34,47},{17,45},{40,48},{17,32},{10,26},{14,28},{46,49},{20,44},{3,44},{9,20},{39,44},{7,18},{11,26},{26,30},{17,22},{22,29},{12,29},{11,45},{18,39},{17,40},{38,39},{42,48},{38,42},{37,50},{45,50},{2,44},{41,44},{22,30},{13,22},{23,31},{27,39},{34,48},{36,37},{18,37},{19,37},{27,48},{44,48},{3,38},{27,37},{1,42},{7,11},{22,33},{14,38},{38,49},{49,50},{12,20},{35,44},{41,47},{5,49},{3,10},{42,44},{31,49},{35,50},{8,29},{24,34},{12,48},{25,46},{26,45},{25,35},{47,48},{29,48},{3,37},{25,29},{6,18},{21,26},{9,36},{9,47},{35,43},{17,31},{30,49},{2,34},{14,35},{2,14},{43,50},{14,29},{38,46},{43,49},{39,47},{21,32},{28,34},{39,40},{15,21},{34,36},{33,37},{4,12},{18,33},{46,50},{20,34},{26,35},{5,19},{41,50},{8,40},{22,40},{30,37},{29,35},{6,47},{11,38},{27,29},{36,45},{7,46},{37,42},{5,12},{34,50},{18,49},{20,39},{44,49},{39,49},{28,33},{8,37},{31,42},{41,46},{42,45},{14,39},{4,14},{1,50},{12,49},{18,50},{25,34},{21,44},{48,49},{1,22},{23,42},{40,44},{4,50},{17,30},{14,45},{11,32},{34,45},{42,46},{40,50},{19,45},{35,48},{26,48},{24,32},{3,46}};
        const auto actual = Solution().possibleBipartition(50, input);
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("submission test 40") {
        vector<vector<int>> input{{4,7},{4,8},{2,8},{8,9},{1,6},{5,8},{1,2},{6,7},{3,10},{8,10},{1,5},{7,10},{1,10},{3,5},{3,6},{1,4},{3,9},{2,3},{1,9},{7,9},{2,7},{6,8},{5,7},{3,4}};
        const auto actual = Solution().possibleBipartition(10, input);
        const auto expected = true;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
