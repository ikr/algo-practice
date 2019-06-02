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

using Words = vector<string>;
using Groups = vector<Words>;

struct Solution final {
    Groups groupAnagrams(const Words& ws) {
        assert(!ws.size());
        return Groups{};
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("empty") {
        const Groups actual = Solution().groupAnagrams(Words{});
        const Groups expected = Groups{};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char** argv) {
    return lest::run(tests, argc, argv);
}
