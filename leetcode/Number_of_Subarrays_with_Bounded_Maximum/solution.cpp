#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

bool range_contains_one_of_indices(const int first, const int last,
                                   const set<int> &m_idx) {
    assert(last - first > 1 && m_idx.size());

    const int lo = *m_idx.begin();
    const int hi = *m_idx.rbegin();

    if (last <= lo || hi < first) return false; // x--x-o--o || o--o-x--x
    if (first <= lo && hi < last) return true;  // o-x--x-o

    // x--o-x--o || o--x-o--x
    return upper_bound(m_idx.cbegin(), m_idx.cend(), first) != m_idx.cend();
}

int count_idx_containing_subranges(const int first, const int last,
                                   const set<int> &m_idx) {
    if (last - first == 1) {
        return m_idx.count(first) ? 1 : 0;
    }

    int ans{0};

    for (int i = first; i != last - 1; ++i) {
        for (int j = i; j != last; ++j) {
            if (range_contains_one_of_indices(first, last, m_idx)) ++ans;
        }
    }

    return ans;
}

struct Solution final {
    int numSubarrayBoundedMax(const vector<int> &xs, const int lo,
                              const int hi) const {
        set<int> m_idx;
        vector<pair<int, int>> ranges;

        optional<int> first;
        for (size_t i = 0; i != xs.size(); ++i) {
            if (!first) {
                if (xs[i] <= hi) first = i;
            } else {
                if (xs[i] > hi) {
                    ranges.push_back({*first, i});
                    first = nullopt;
                }
            }

            if (lo <= xs[i] && xs[i] <= hi) m_idx.insert(i);
        }

        if (m_idx.empty()) return 0;

        int ans{0};

        for (const auto [first, last] : ranges) {
            ans += count_idx_containing_subranges(first, last, m_idx);
        }

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
    CASE("propblem statement example") {
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
    CASE("tail-only") {
        const auto actual = Solution().numSubarrayBoundedMax({2,2,2,1}, 1, 1);
        const auto expected = 1;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
