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
        TestCase{{3, 2, 2, 4, 3}, 3, 2}, TestCase{{7, 3, 4, 7}, 7, 2},
        TestCase{{4, 3, 2, 6, 2, 3, 4}, 6, -1},
        TestCase{{5, 5, 4, 4, 5}, 3, -1},
        TestCase{{3, 1, 1, 1, 5, 1, 2, 1}, 3, 3}, TestCase{{1, 6, 1}, 7, -1});

    const auto actual = Solution{}.minSumOfLengths(xs, t);
    REQUIRE(actual == expected);
}
