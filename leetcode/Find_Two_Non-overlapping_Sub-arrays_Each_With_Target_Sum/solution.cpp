#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <bits/stdc++.h>
using namespace std;

using pi = pair<int, int>;
using vi = vector<int>;
using vpi = vector<pi>;

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

constexpr bool intersect(const pi r1, const pi r2) {
    const auto [a, b] = r1;
    const auto [c, d] = r2;

    return (c <= b && b <= d) || (c <= a && a <= d);
}

constexpr int length(const pi r) { return r.second - r.first + 1; }

struct Cmp final {
    bool operator()(const pi lhs, const pi rhs) const {
        return length(lhs) > length(rhs);
    }
};

int optimal_lengths_sum(vpi ranges) {
    if (ranges.empty()) return -1;

    const pi r1 = ranges.front();
    pop_heap(ranges.begin(), ranges.end(), Cmp{});
    ranges.pop_back();

    while (!ranges.empty()) {
        const pi r2 = ranges.front();
        pop_heap(ranges.begin(), ranges.end(), Cmp{});
        ranges.pop_back();

        if (intersect(r1, r2)) continue;
        return length(r1) + length(r2);
    }

    return -1;
}

struct Solution {
    int minSumOfLengths(const vi &xs, const int t) const {
        if (xs.empty()) return -1;

        vpi ranges;
        const int sz = xs.size();
        int lo = 0, hi = 0, s = xs.front();

        do {
            if (s == t) {
                ranges.emplace_back(lo, hi);
                push_heap(ranges.begin(), ranges.end(), Cmp{});
            }
            step(xs, t, s, lo, hi);
        } while (lo < sz);

        return optimal_lengths_sum(ranges);
    }
};

using TestCase = tuple<vi, int, int>;

TEST_CASE("Solution") {
    const auto [xs, t, expected] = GENERATE(
                                            TestCase{{}, 1, -1}, TestCase{{1},1,-1}, TestCase{{1,1,1,1}, 2, 4},
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
