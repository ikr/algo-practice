#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

namespace kactl { // https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/Eratosthenes.h
static constexpr int UpperBound = 10'000'000;
static auto IsPrime = []() -> bitset<UpperBound> {
    bitset<UpperBound> isprime;
    isprime.set();
    isprime[0] = isprime[1] = 0;
    for (int i = 4; i < UpperBound; i += 2) isprime[i] = 0;
    for (int i = 3; i * i < UpperBound; i += 2) {
        if (isprime[i]) {
            for (int j = i * i; j < UpperBound; j += i * 2) {
                isprime[j] = 0;
            }
        }
    }
    return isprime;
}();
} // namespace kactl

struct SquidGamesBridge final {
    int cross(int P, const int S) const {
        int fallen{};
        for (int iplayer{}, isection{}; isection < S; ++isection) {
            while (iplayer < P &&
                   (iplayer % 2 == 0) != kactl::IsPrime[isection]) {
                ++iplayer;
                ++fallen;
            }

            if (iplayer == P) break;
        }
        return P - fallen;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = SquidGamesBridge{}.cross(3, 2);
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = SquidGamesBridge{}.cross(3, 4);
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = SquidGamesBridge{}.cross(3, 5);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = SquidGamesBridge{}.cross(1234567, 1);
        const auto expected = 1234566;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = SquidGamesBridge{}.cross(1234, 567);
        const auto expected = 1029;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
