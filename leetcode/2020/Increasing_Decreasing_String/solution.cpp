#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

namespace {
void prune(map<char, int> &m) {
    for (auto it = m.begin(); it != m.end();) {
        if (it->second == 0) {
            it = m.erase(it);
        } else {
            ++it;
        }
    }
}
} // namespace

struct Solution final {
    string sortString(const string &s) const {
        map<char, int> counts_by_char;

        for (const char c : s) {
            ++counts_by_char[c];
        }

        string ans;

        while (!counts_by_char.empty()) {
            for (auto it = counts_by_char.begin(); it != counts_by_char.end();
                 ++it) {
                ans += it->first;
                --it->second;
            }

            prune(counts_by_char);

            for (auto it = counts_by_char.rbegin(); it != counts_by_char.rend();
                 ++it) {
                ans += it->first;
                --it->second;
            }

            prune(counts_by_char);
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Ex 1") {
        const auto actual = Solution{}.sortString("aaaabbbbcccc");
        const auto expected = "abccbaabccba";
        EXPECT(actual == expected);
    },
    CASE("Ex 2") {
        const auto actual = Solution{}.sortString("rat");
        const auto expected = "art";
        EXPECT(actual == expected);
    },
    CASE("Ex 3") {
        const auto actual = Solution{}.sortString("leetcode");
        const auto expected = "cdelotee";
        EXPECT(actual == expected);
    },
    CASE("Ex 4") {
        const auto actual = Solution{}.sortString("ggggggg");
        const auto expected = "ggggggg";
        EXPECT(actual == expected);
    },
    CASE("Ex 5") {
        const auto actual = Solution{}.sortString("spo");
        const auto expected = "ops";
        EXPECT(actual == expected);
    },
    CASE("Empty") {
        const auto actual = Solution{}.sortString("");
        const auto expected = "";
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
