#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

namespace {
int families_count(const vector<bool> &row) {
    assert(row.size() == 10);

    if (count(row.cbegin() + 1, row.cbegin() + 9, true) == 8) return 2;

    if (count(row.cbegin() + 1, row.cbegin() + 5, true) == 4 ||
        count(row.cbegin() + 3, row.cbegin() + 7, true) == 4 ||
        count(row.cbegin() + 5, row.cbegin() + 9, true) == 4) {
        return 1;
    }

    return 0;
}
} // namespace

struct Solution final {
    int maxNumberOfFamilies(const int n, const vector<vector<int>> &reserved) const {
        vector<vector<bool>> seats(n, vector<bool>(10, true));

        for (const auto &rowcol : reserved) {
            const int row = rowcol[0] - 1;
            const int col = rowcol[1] - 1;

            seats[row][col] = false;
        }

        int ans = 0;

        for (const auto &row : seats) {
            ans += families_count(row);
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 1") {
        const auto actual = Solution{}.maxNumberOfFamilies(3, {{1,2},{1,3},{1,8},{2,6},{3,1},{3,10}});
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = Solution{}.maxNumberOfFamilies(2, {{2,1},{1,8},{2,6}});
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = Solution{}.maxNumberOfFamilies(4, {{4,3},{1,4},{4,6},{1,7}});
        const auto expected = 4;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
