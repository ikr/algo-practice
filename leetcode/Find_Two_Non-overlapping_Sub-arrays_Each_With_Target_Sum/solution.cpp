#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

void step(const vi &xs, const int t, int &s, int &lo, int &hi) {
    const int sz = xs.size();

    if (s == t) {
        ++lo;
        hi = lo;
        if (lo < sz) s = xs[lo];
    } else if (s < t) {
        ++hi;
        if (hi < sz)
            s += xs[hi];
        else {
            ++lo;
            hi = lo;
            if (lo < sz) s = xs[lo];
        }
    } else {
        assert(s > t);
        s -= xs[lo];
        ++lo;
    }
}

vi optimum_at_prefix_length(const vi &xs, const int t) {
    const int sz = xs.size();
    vi ans(sz + 1, INT_MAX);
    int lo = 0, hi = 0, s = xs.front();

    do {
        if (s == t) ans[hi + 1] = min(ans[hi + 1], hi - lo + 1);
        step(xs, t, s, lo, hi);
    } while (lo < sz);

    for (int i = 2; i <= sz; ++i) ans[i] = min(ans[i], ans[i - 1]);
    return ans;
}

struct Solution {
    int minSumOfLengths(const vi &xs, const int t) const {
        if (xs.empty()) return -1;
        const auto ltr = optimum_at_prefix_length(xs, t);

        const vi ys(xs.crbegin(), xs.crend());
        const auto rtl = optimum_at_prefix_length(ys, t);

        const int sz = xs.size();
        int ans = INT_MAX;
        for (int i = 1; i < sz; ++i) {
            const int prefix_length = i;
            const int suffix_length = sz - i;

            if (ltr[prefix_length] != INT_MAX &&
                rtl[suffix_length] != INT_MAX) {
                ans = min(ans, ltr[prefix_length] + rtl[suffix_length]);
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};

using TestCase = tuple<vi, int, int>;

TEST_CASE("Solution") {
    const auto [xs, t, expected] = GENERATE(
        TestCase{{}, 1, -1}, TestCase{{1}, 1, -1}, TestCase{{1, 1, 1, 1}, 2, 4},
        TestCase{{3, 2, 2, 4, 3}, 3, 2}, TestCase{{7, 3, 4, 7}, 7, 2},
        TestCase{{4, 3, 2, 6, 2, 3, 4}, 6, -1},
        TestCase{{5, 5, 4, 4, 5}, 3, -1},
        TestCase{{3, 1, 1, 1, 5, 1, 2, 1}, 3, 3}, TestCase{{1, 6, 1}, 7, -1},
        TestCase{
            {78, 18, 1,  94, 1,  1,  1,  29, 58, 3,  4,  1,  2,  56, 17, 19, 4,
             1,  63, 2,  16, 11, 1,  1,  2,  1,  25, 62, 10, 69, 12, 7,  1,  6,
             2,  92, 4,  1,  61, 7,  26, 1,  1,  1,  67, 26, 2,  2,  70, 25, 2,
             68, 13, 4,  11, 1,  34, 14, 7,  37, 4,  1,  12, 51, 25, 2,  4,  3,
             56, 21, 7,  8,  5,  93, 1,  1,  2,  55, 14, 25, 1,  1,  1,  89, 6,
             1,  1,  24, 22, 50, 1,  28, 9,  51, 9,  88, 1,  7,  1,  30, 32, 18,
             12, 3,  2,  18, 10, 4,  11, 43, 6,  5,  93, 2,  2,  68, 18, 11, 47,
             33, 17, 27, 56, 13, 1,  2,  29, 1,  17, 1,  10, 15, 18, 3,  1,  86,
             7,  4,  16, 45, 3,  29, 2,  1,  1,  31, 19, 18, 16, 12, 1,  56, 4,
             35, 1,  1,  36, 59, 1,  1,  16, 58, 18, 4,  1,  43, 31, 15, 6,  1,
             1,  6,  49, 27, 12, 1,  2,  80, 14, 2,  1,  21, 32, 18, 15, 11, 59,
             10, 1,  14, 3,  3,  7,  15, 4,  55, 4,  1,  12, 4,  1,  1,  53, 37,
             2,  5,  72, 3,  6,  10, 3,  3,  83, 8,  1,  5},
            97,
            5},
        TestCase{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1,
                  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                 10,
                 19});

    const auto actual = Solution{}.minSumOfLengths(xs, t);
    REQUIRE(actual == expected);
}
