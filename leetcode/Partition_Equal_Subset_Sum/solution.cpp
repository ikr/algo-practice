#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

template <typename T> int intof(const T x) { return static_cast<int>(x); }

struct Solution final {
    bool canPartition(const vector<int> &xs) const {
        const int total_sum = accumulate(cbegin(xs), cend(xs), 0);

        if (total_sum % 2 ||
            any_of(cbegin(xs), cend(xs),
                   [total_sum](const int x) { return x > total_sum / 2; }))
            return false;

        vector<vector<bool>> ans(xs.size());
        for (auto &row : ans) row = vector<bool>(total_sum / 2 + 1);
        for (int i = 0; i != intof(xs.size()); ++i) ans[i][xs[i]] = true;

        for (int i = 1; i != intof(xs.size()); ++i)
            for (int j = 1; j <= total_sum / 2; ++j) {
                ans[i][j] = ans[i - 1][j];

                if (j - xs[i] >= 0)
                    ans[i][j] = ans[i][j] || ans[i - 1][j - xs[i]];
            }

        return ans[xs.size() - 1][total_sum / 2];
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Problem statement example 1") {
        const auto actual = Solution().canPartition({1, 5, 11, 5});
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("Problem statement example 2") {
        const auto actual = Solution().canPartition({1, 2, 3, 5});
        const auto expected = false;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
