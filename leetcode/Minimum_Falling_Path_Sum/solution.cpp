#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    int minFallingPathSum(vector<vector<int>> &rows) const {
        if (rows.empty() || rows[0].empty()) return INT_MAX;

        for (unsigned int i = 1; i < rows.size(); ++i) {
            for (unsigned int j = 0; j != rows[i].size(); ++j) {
                const int own = rows[i][j];
                rows[i][j] = own + rows[i - 1][j];

                if (j) rows[i][j] = min(rows[i][j], own + rows[i - 1][j - 1]);

                if (j != rows[i].size() - 1)
                    rows[i][j] = min(rows[i][j], own + rows[i - 1][j + 1]);
            }
        }

        const auto m_it = min_element(rows.back().cbegin(), rows.back().cend());
        return *m_it;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Problem statement example 1") {
        vector<vector<int>> rows{{1,2,3},{4,5,6},{7,8,9}};
        const auto actual = Solution().minFallingPathSum(rows);
        const auto expected = 12;
        EXPECT(actual == expected);
    },
    CASE("Degenerate 1") {
        vector<vector<int>> rows{};
        const auto actual = Solution().minFallingPathSum(rows);
        const auto expected = INT_MAX;
        EXPECT(actual == expected);
    },
    CASE("Degenerate 2") {
        vector<vector<int>> rows{{},{},{}};
        const auto actual = Solution().minFallingPathSum(rows);
        const auto expected = INT_MAX;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
