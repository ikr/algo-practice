#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 1e9 + 7;

struct Solution final {
    int numOfSubarrays(const vector<int> &xs) const {
        const int sz = xs.size();
        vector<int> indices_of_odds;

        for (int i = 0; i < sz; i++) {
            if (xs[i] % 2) indices_of_odds.push_back(i);
        }

        if (indices_of_odds.empty()) return 0;
        const int osz = indices_of_odds.size();
        ll ans = 0;

        for (int i = 0; i < osz; ++i) {
            for (int j = i; j < osz; j += 2) {
                const int lo = indices_of_odds[i];
                const int hi = indices_of_odds[j];

                ll l = (i == 0 ? lo + 1 : lo - indices_of_odds[i - 1]);
                ll r = (j == osz - 1 ? sz - hi : indices_of_odds[i + 1] - hi);

                ans += l * r;
                ans %= M;
            }
        }

        return ans;
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
