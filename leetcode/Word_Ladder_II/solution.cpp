#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;
using vs = vector<string>;
using vvs = vector<vs>;

struct Solution final {
    vvs findLadders(const string &s, const string &t, const vs &dict)  const {
        return {};
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 1") {
        const vs dict{"hot","dot","dog","lot","log","cog"};
        auto actual = Solution{}.findLadders("hit", "cog", dict);
        sort(actual.begin(), actual.end());
        const vvs expected{{"hit","hot","dot","dog","cog"},{"hit","hot","lot","log","cog"}};
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const vs dict{"hot","dot","dog","lot","log"};
        const auto actual = Solution{}.findLadders("hit", "cog", dict);
        const vvs expected{};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
