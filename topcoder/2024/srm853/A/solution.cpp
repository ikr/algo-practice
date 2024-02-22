#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

struct SkyscraperElevator final {
    int simulate(const int N, const vector<int> &xs) const {
        assert(N > 0);
        int result{};
        int cur{};

        for (const auto x : xs) {
            const auto walking_time = x * 20;
            const auto riding_time = cur + x;

            if (walking_time < riding_time) {
                result += walking_time;
            } else {
                result += riding_time;
                cur = x;
            }
        }

        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = SkyscraperElevator{}.simulate(1000000, {1000000, 1000000, 1000000, 7, 500000});
        const auto expected = 6500140;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = SkyscraperElevator{}.simulate(47000, {19, 1, 1000});
        const auto expected = 1040;
        EXPECT(actual == expected);
    },
    CASE("Example A") {
        const auto actual = SkyscraperElevator{}.simulate(1, {1});
        const auto expected = 1;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
