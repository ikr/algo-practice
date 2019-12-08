#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    string decodeString(const string &source) const {
        return source.substr(source.size() - 1);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Problem statement example 1") {
        const auto actual = Solution().decodeString("3[a]2[bc]");
        const auto expected = "aaabcbc";
        EXPECT(actual == expected);
    },
    CASE("Problem statement example 2") {
        const auto actual = Solution().decodeString("3[a2[c]]");
        const auto expected = "accaccacc";
        EXPECT(actual == expected);
    },
    CASE("Problem statement example 3") {
        const auto actual = Solution().decodeString("2[abc]3[cd]ef");
        const auto expected = "abcabccdcdcdef";
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char** argv) {
    return lest::run(tests, argc, argv);
}
