#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using Words = vector<string>;
using Groups = vector<Words>;

struct Solution final {
    Groups groupAnagrams(const Words &ws) {
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

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
