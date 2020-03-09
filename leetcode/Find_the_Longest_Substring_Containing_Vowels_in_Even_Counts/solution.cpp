#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

namespace {
const unordered_map<char, int> vowel_index{
    {'a', 0}, {'e', 1}, {'i', 2}, {'o', 3}, {'u', 4}};
} // namespace

struct Solution final {
    int findTheLongestSubstring(const string &s) const {
        int ans = 0;
        vector<int> first_index_at_parity(32, -1);
        first_index_at_parity[0] = 0;

        for (auto i = 0U, parity = 0U; i != s.size(); ++i) {
            if (vowel_index.count(s[i])) {
                parity ^= (1 << vowel_index.at(s[i]));
            }

            if (first_index_at_parity[parity] < 0) {
                first_index_at_parity[parity] = i + 1;
            } else {
                const int candidate = i - first_index_at_parity[parity] + 1;
                if (candidate > ans) ans = candidate;
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
    CASE("ewwwedxe") {
        const auto actual = Solution{}.findTheLongestSubstring("ewwwedxe");
        const auto expected = 7;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
