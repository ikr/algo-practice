#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using ui_t = unsigned int;

constexpr ui_t bits_required(const ui_t x) {
    return static_cast<ui_t>(log2(x)) + 1;
}

ui_t count_for_bits(const ui_t n) {
    static unordered_map<ui_t, ui_t> cache{{0, 0}, {1, 2}, {2, 3}};
    if (cache.count(n)) return cache[n];

    cache[n] = count_for_bits(n - 1) + count_for_bits(n - 2);
    return cache[n];
}

ui_t count_for(const ui_t x) {
    ui_t ans{0};
    ui_t prev_bit{0};
    ui_t i = bits_required(x) - 1;

    for (;;) {
        ui_t bit = prev_bit ? 0 : (x & (1 << i));

        if (!i) {
            ans += bit ? 2 : 1;
            break;
        }

        if (bit) ans += count_for_bits(i);
        --i;
        prev_bit = bit;
    }

    return ans;
}

struct Solution final {
    ui_t findIntegers(const ui_t x) const { return count_for(x); }
};

// clang-format off
const lest::test tests[] = {
    CASE("Problem statement example") {
        const ui_t actual = Solution().findIntegers(5);
        const ui_t expected = 5;
        EXPECT(actual == expected);
    },
    CASE("0") {
        const ui_t actual = Solution().findIntegers(0);
        const ui_t expected = 1;
        EXPECT(actual == expected);
    },
    CASE("1") {
        const ui_t actual = Solution().findIntegers(1);
        const ui_t expected = 2;
        EXPECT(actual == expected);
    },
    CASE("2") {
        const ui_t actual = Solution().findIntegers(2);
        const ui_t expected = 3;
        EXPECT(actual == expected);
    },
    CASE("3") {
        const ui_t actual = Solution().findIntegers(3);
        const ui_t expected = 3;
        EXPECT(actual == expected);
    },
    CASE("4") {
        const ui_t actual = Solution().findIntegers(4);
        const ui_t expected = 4;
        EXPECT(actual == expected);
    },
    CASE("5") {
        const ui_t actual = Solution().findIntegers(5);
        const ui_t expected = 5;
        EXPECT(actual == expected);
    },
    CASE("6") {
        const ui_t actual = Solution().findIntegers(6);
        const ui_t expected = 5;
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
    CASE("31") {
        const ui_t actual = Solution().findIntegers(31);
        const ui_t expected = 13;
        EXPECT(actual == expected);
    },
    CASE("9000") {
        const ui_t actual = Solution().findIntegers(9000);
        const ui_t expected = 754;
        EXPECT(actual == expected);
    },
    CASE("161179") {
        const ui_t actual = Solution().findIntegers(161179);
        const ui_t expected = 5778;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
