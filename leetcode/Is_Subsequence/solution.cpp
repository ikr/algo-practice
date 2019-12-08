#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    bool isSubsequence(const string &s, const string &t) const {
        if (!s.size()) return true;
        unsigned int i = 0;

        for (const char c : t) {
            if (s[i] == c) {
                ++i;
                if (i == s.size()) break;
            }
        }

        return i == s.size();
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Problem statement example 1") {
        const auto actual = Solution().isSubsequence("abc", "ahbgdc");
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("Problem statement example 2") {
        const auto actual = Solution().isSubsequence("axc", "ahbgdc");
        const auto expected = false;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char** argv) {
    return lest::run(tests, argc, argv);
}
