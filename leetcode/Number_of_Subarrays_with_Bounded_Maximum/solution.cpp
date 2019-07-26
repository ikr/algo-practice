#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using Iter = vector<int>::const_iterator;
using PRange = tuple<Iter, Iter, Iter>;
using Bounds = pair<int, int>;

int count_subranges_continuous(const Bounds bounds, const PRange prange) {
    return 0;
}

int count_subranges(const Bounds bounds, const vector<int> &xs) {
    const auto [lo, hi] = bounds;
    const auto end = xs.cend();

    vector<PRange> p_ranges;
    optional<Iter> maybe_r;

    while (!maybe_r || *maybe_r != end) {
        const Iter l = find_if(maybe_r ? *maybe_r : xs.begin(), end,
                               [hi](const int x) { return x <= hi; });
        if (l == end) break;

        const Iter r = find_if(l, end, [hi](const int x) { return x > hi; });

        const Iter p =
            find_if(l, r, [lo, hi](const int x) { return lo <= x && x <= hi; });
        if (p != r) p_ranges.emplace_back(l, p, r);

        maybe_r = r;
    }

    return transform_reduce(p_ranges.cbegin(), p_ranges.cend(), 0, plus<int>{},
                            [bounds](const PRange pr) {
                                return count_subranges_continuous(bounds, pr);
                            });
}

struct Solution final {
    int numSubarrayBoundedMax(const vector<int> &xs, const int lo,
                              const int hi) const {
        return count_subranges({lo, hi}, xs);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("empty") {
        const auto actual = Solution().numSubarrayBoundedMax({}, 1, 2);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("full") {
        const auto actual = Solution().numSubarrayBoundedMax({1,1,1,1}, 1, 2);
        const auto expected = 10;
        EXPECT(actual == expected);
    },
    CASE("problem statement example") {
        const auto actual = Solution().numSubarrayBoundedMax({2,1,4,3}, 2, 3);
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("leetcode test 3") {
        const auto actual = Solution().numSubarrayBoundedMax({2,9,2,5,6}, 2, 8);
        const auto expected = 7;
        EXPECT(actual == expected);
    },
    CASE("random 1") {
        const auto actual = Solution().numSubarrayBoundedMax({1,2,3,1,2}, 1, 2);
        const auto expected = 6;
        EXPECT(actual == expected);
    },
    CASE("random 2") {
        const auto actual = Solution().numSubarrayBoundedMax({6,9,2,7,4,7,1,8,5}, 4, 7);
        const auto expected = 15;
        EXPECT(actual == expected);
    },
    CASE("PI 8 9") {
        const auto actual = Solution().numSubarrayBoundedMax({3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3}, 8, 9);
        const auto expected = 104;
        EXPECT(actual == expected);
    },
    CASE("head-only") {
        const auto actual = Solution().numSubarrayBoundedMax({1,2,2}, 1, 1);
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("huge") {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 9);

        vector<int> xs(20000);
        for (auto &x : xs) {
            x = dis(gen);
        }

        const auto actual = Solution().numSubarrayBoundedMax(xs, 7, 8);
        EXPECT(actual > 0);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
