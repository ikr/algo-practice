#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    int findTheDistanceValue(vector<int> &xs, vector<int> &ys,
                             const int d) const {
        int ans = 0;

        for (const int x : xs) {
            bool ok = true;

            for (const int y : ys) {
                if (abs(x - y) <= d) {
                    ok = false;
                    break;
                }
            }

            if (ok) ++ans;
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 1") {
        vector<int> xs{1,4,2,3};
        vector<int> ys{-4,-3,6,10,20,30};
        const int d = 3;
        const int actual = Solution{}.findTheDistanceValue(xs, ys, d);
        const int expected = 2;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        vector<int> xs{2,1,100,3};
        vector<int> ys{-5,-2,10,-3,7};
        const int d = 6;
        const int actual = Solution{}.findTheDistanceValue(xs, ys, d);
        const int expected = 1;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
