#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

template <typename T> int intof(const T x) { return static_cast<int>(x); }
using Iter = vector<int>::const_iterator;

int count_proper_suffixes(const pair<int, int> bounds, Iter first, Iter pillar,
                          Iter last) {
    if (first == last) return 0;

    auto [lo, hi] = bounds;
    if (first == pillar) {
        pillar = find_if(first + 1, last,
                         [lo, hi](const int x) { return lo <= x && x <= hi; });
        if (pillar == last) return 0;
    }

    ++first;
    int ans = 0;

    ans += distance(first, last);
    ans += count_proper_suffixes({lo, hi}, first + 1, pillar, last);

    return ans;
}

struct Solution final {
    int numSubarrayBoundedMax(const vector<int> &xs, const int lo,
                              const int hi) const {
        int l = -1;
        int ans = 0;

        do {
            auto first = find_if(xs.cbegin() + (l + 1), xs.cend(),
                                 [hi](const int x) { return x <= hi; });
            if (first == xs.cend()) break;

            auto pillar = find_if(first, xs.cend(), [lo, hi](const int x) {
                return lo <= x && x <= hi;
            });
            if (pillar == xs.cend()) break;

            auto last = find_if(pillar + 1, xs.cend(),
                                [hi](const int x) { return hi < x; });

            ans += distance(xs.cbegin(), last);
            ans += count_proper_suffixes({lo, hi}, first, pillar, last);
            l = distance(xs.cbegin(), last);
        } while (l != intof(xs.size()));

        return ans;
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
