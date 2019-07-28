#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using ui_t = unsigned int;

constexpr ui_t bits_required(const ui_t x) {
    return static_cast<ui_t>(log2(x)) + 1;
}

ui_t count_for_bits(const ui_t n) {
    static vector<ui_t> cache{0, 2, 3};
    if (n < cache.size()) return cache[n];

    cache.resize(n + 1);
    cache[n] = count_for_bits(n - 1) + count_for_bits(n - 2);
    return cache[n];
}

struct Solution final {
    ui_t findIntegers(const ui_t x) const {
        return count_for_bits(bits_required(x));
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Problem statement example") {
        const ui_t actual = Solution().findIntegers(5);
        const ui_t expected = 5;
        EXPECT(actual == expected);
    },
    CASE("1") {
        const ui_t actual = Solution().findIntegers(1);
        const ui_t expected = 2;
        EXPECT(actual == expected);
    },
    CASE("3") {
        const ui_t actual = Solution().findIntegers(3);
        const ui_t expected = 3;
        EXPECT(actual == expected);
    },
    CASE("7") {
        const ui_t actual = Solution().findIntegers(7);
        const ui_t expected = 5;
        EXPECT(actual == expected);
    },
    CASE("15") {
        const ui_t actual = Solution().findIntegers(15);
        const ui_t expected = 8;
        EXPECT(actual == expected);
    },
    CASE("9000") {
        const ui_t actual = Solution().findIntegers(9000);
        const ui_t expected = 754;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
