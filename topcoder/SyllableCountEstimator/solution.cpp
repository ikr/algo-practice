#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

struct SyllableCountEstimator final {
    int estimate(const string &word) const {
        const int n = word.size();
        const set<char> all_vows{'a', 'e', 'i', 'o', 'u'};
        const set<string> all_exps{"au", "oa", "oo", "iou"};

        int vows = 0;
        int exps = 0;

        for (int i = 0; i < n; ++i) {
            const char s1 = word[i];
            const string s2 = i + 1 < n ? word.substr(i, 2) : "~";
            const string s3 = i + 2 < n ? word.substr(i, 3) : "~";

            if (all_vows.count(s1)) ++vows;
            if (all_exps.count(s2) || all_exps.count(s3)) ++exps;
        }

        int ans = vows - exps;
        if (word.back() == 'e') --ans;

        if (n >= 3 && !all_vows.count(word[n - 3]) &&
            word.substr(n - 2) == "le") {
            ++ans;
        }

        return ans < 1 ? 1 : ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = SyllableCountEstimator{}.estimate("potato");
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = SyllableCountEstimator{}.estimate("haul");
        const auto expected = 1;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
