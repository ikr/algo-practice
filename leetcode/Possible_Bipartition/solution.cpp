#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

bool can_split_in_two_groups(unordered_set<int> ga, unordered_set<int> gb,
                             vector<vector<int>> &dislikes) {
    while (dislikes.size()) {
        const vector<int> dl = dislikes.back();
        dislikes.pop_back();

        const int x = dl.front();
        const int y = dl.back();

        if (!ga.size()) {
            ga.insert(x);
            gb.insert(y);
        } else if (!ga.count(x) && !gb.count(y) && !ga.count(y) &&
                   !gb.count(x)) {
            ga.insert(x);
            gb.insert(y);
            if (can_split_in_two_groups(ga, gb, dislikes)) return true;

            ga.erase(x);
            gb.erase(y);
            ga.insert(y);
            gb.insert(x);
            return can_split_in_two_groups(ga, gb, dislikes);
        } else if (ga.count(x)) {
            if (ga.count(y)) return false;
            gb.insert(y);
        } else if (ga.count(y)) {
            if (ga.count(x)) return false;
            gb.insert(x);
        } else if (gb.count(x)) {
            if (gb.count(y)) return false;
            ga.insert(y);
        } else if (gb.count(y)) {
            if (gb.count(x)) return false;
            ga.insert(x);
        } else
            return false;
    }

    return true;
}

struct Solution final {
    bool possibleBipartition(const int sz, vector<vector<int>> &dislikes) {
        assert(sz);
        return can_split_in_two_groups(unordered_set<int>{},
                                       unordered_set<int>{}, dislikes);
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
    CASE("submission test 40") {
        vector<vector<int>> input{{4,7},{4,8},{2,8},{8,9},{1,6},{5,8},{1,2},{6,7},{3,10},{8,10},{1,5},{7,10},{1,10},{3,5},{3,6},{1,4},{3,9},{2,3},{1,9},{7,9},{2,7},{6,8},{5,7},{3,4}};
        const auto actual = Solution().possibleBipartition(10, input);
        const auto expected = true;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
