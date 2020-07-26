#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
static constexpr ll M = 1e9 + 7;

struct Solution final {
    int numOfSubarrays(const vi &xs) const {
        if (xs.empty()) return 0;
        const int sz = xs.size();

        // DP[i] — count of subarrays with even sum, ending at index i
        vi ev(sz, 0);

        // DP[i] — count of subarrays with odd sum, ending at index i
        vi od(sz, 0);

        if (xs[0] % 2)
            od[0] = 1;
        else
            ev[0] = 1;

        for (int i = 1; i < sz; ++i) {
            if (xs[i] % 2) {
                od[i] = ev[i - 1] + 1;
                ev[i] = od[i - 1];
            } else {
                ev[i] = ev[i - 1] + 1;
                od[i] = od[i - 1];
            }
        }

        return accumulate(od.cbegin(), od.cend(), 0LL, plus<ll>{}) % M;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 1") {
        const auto actual = Solution{}.numOfSubarrays({1,3,5});
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = Solution{}.numOfSubarrays({2,4,6});
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = Solution{}.numOfSubarrays({1,2,3,4,5,6,7});
        const auto expected = 16;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = Solution{}.numOfSubarrays({100,100,99,99});
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("Example 5") {
        const auto actual = Solution{}.numOfSubarrays({7});
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example from GeeksforGeeks") {
        const auto actual = Solution{}.numOfSubarrays({5,4,4,5,1,3});
        const auto expected = 12;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
