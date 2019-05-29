#include "lest.hpp"
#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <locale>
#include <map>
#include <numeric>
#include <optional>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
using vec = vector<int>;
using vvec = vector<vector<int>>;
using mapii = map<int, int>;

vec append(vec xs, int y) {
    xs.push_back(y);
    return xs;
}

mapii take_out(mapii count_by_x, int x) {
    assert(count_by_x.count(x));
    count_by_x[x]--;
    if (!count_by_x[x]) count_by_x.erase(x);
    return count_by_x;
}

void permute_recur(const vec &prefix, const mapii &count_by_x, vvec &result) {
    if (!count_by_x.size()) {
        result.push_back(prefix);
        return;
    }

    for (const auto i : count_by_x) {
        const int x = i.first;
        assert(i.second > 0);
        permute_recur(append(prefix, x), take_out(count_by_x, x), result);
    }
}

mapii count_elements(const vec &xs) {
    mapii result;

    for (const int x : xs) {
        result[x]++;
    }

    return result;
}

struct Solution {
    vvec permuteUnique(const vec &xs) {
        vvec result{};
        permute_recur(vec{}, count_elements(xs), result);
        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("take_out works") {
        const auto actual = take_out(mapii{{42, 1}}, 42);
        const auto expected = mapii{};
        EXPECT(actual == expected);
    },
    CASE("empty output on empty input") {
        const auto actual = Solution().permuteUnique(vector<int>{});
        const auto expected = vector<vector<int>>{{}};
        EXPECT(actual == expected);
    },
    CASE("trivial 1-element input") {
        const auto actual = Solution().permuteUnique(vector<int>{42});
        const auto expected = vector<vector<int>>{{42}};
        EXPECT(actual == expected);
    },
    CASE("example from the problem statement") {
        const auto actual = Solution().permuteUnique(vector<int>{1,1,2});
        const auto expected = vector<vector<int>>{{1,1,2},{1,2,1},{2,1,1}};
        EXPECT(actual == expected);
    },
    CASE("three ones") {
        const auto actual = Solution().permuteUnique(vector<int>{1,1,1});
        const auto expected = vector<vector<int>>{{1,1,1}};
        EXPECT(actual == expected);
    },
    CASE("1,2,3") {
        const auto actual = Solution().permuteUnique(vector<int>{1,2,3});
        const auto expected = vector<vector<int>>{{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}};
        EXPECT(actual == expected);
    },
    CASE("64 1-s") {
        const auto actual = Solution().permuteUnique(vector<int>{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1});
        const auto expected = vector<vector<int>>{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
