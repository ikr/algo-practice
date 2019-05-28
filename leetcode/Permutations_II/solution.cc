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

vec append(vec xs, int y) {
    xs.push_back(y);
    return xs;
}

map<int, int> take_out(map<int, int> count_by_x, int x) {
    assert(count_by_x.count(x));
    count_by_x[x]--;
    if (!count_by_x[x]) count_by_x.erase(x);
    return count_by_x;
}

void permute_recur(const vec &prefix, const map<int, int> &count_by_x,
                   vvec &result) {
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

map<int, int> count_elements(const vec &xs) {
    map<int, int> result;

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

int answer_to_life_universe_and_everything() { return -1; }

// clang-format off
const lest::test tests[] = {
    CASE("take_out works") {
        const auto actual = take_out(map<int, int>{{42, 1}}, 42);
        const auto expected = map<int, int>{};
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
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
