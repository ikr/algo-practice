#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    int findTheLongestSubstring(const string &s) const {
        int ans = 0;

        for (auto b = 0U; b != s.size(); ++b) {
            bool a = true;
            bool e = true;
            bool i = true;
            bool o = true;
            bool u = true;

            for (auto j = b; j != s.size(); ++j) {
                switch (s[j]) {
                case 'a':
                    a = !a;
                    break;

                case 'e':
                    e = !e;
                    break;

                case 'i':
                    i = !i;
                    break;

                case 'o':
                    o = !o;
                    break;

                case 'u':
                    u = !u;
                    break;
                }

                if (a && e && i && o && u) {
                    if (static_cast<int>(j - b + 1) > ans) {
                        ans = j - b + 1;
                    }
                }
            }
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Ex 1") {
        const auto actual = Solution{}.findTheLongestSubstring("eleetminicoworoep");
        const auto expected = 13;
        EXPECT(actual == expected);
    },
    CASE("Ex 2") {
        const auto actual = Solution{}.findTheLongestSubstring("leetcodeisgreat");
        const auto expected = 5;
        EXPECT(actual == expected);
    },
    CASE("Ex 3") {
        const auto actual = Solution{}.findTheLongestSubstring("bcbcbc");
        const auto expected = 6;
        EXPECT(actual == expected);
    },
    CASE("Empty") {
        const auto actual = Solution{}.findTheLongestSubstring("");
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("aa") {
        const auto actual = Solution{}.findTheLongestSubstring("aa");
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("xx") {
        const auto actual = Solution{}.findTheLongestSubstring("xx");
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("abba") {
        const auto actual = Solution{}.findTheLongestSubstring("abba");
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("a") {
        const auto actual = Solution{}.findTheLongestSubstring("a");
        const auto expected = 0;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
