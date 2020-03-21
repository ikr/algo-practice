#include "lest.hpp"
#include <algorithm>
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

namespace {
int power(unordered_map<int, int> &memo, const int x) {
    if (!memo.count(x)) {
        if (x == 1) {
            memo[x] = 0;
        } else {
            memo[x] = 1 + power(memo, x % 2 ? x * 3 + 1 : x / 2);
        }
    }

    return memo.at(x);
}
} // namespace

struct Solution final {
    int getKth(const int lo, const int hi, const int k) const {
        unordered_map<int, int> memo;

        vector<int> xs(hi - lo + 1);
        iota(xs.begin(), xs.end(), lo);

        nth_element(xs.begin(), xs.begin() + k - 1, xs.end(),
                    [&memo](const int x, const int y) {
                        const int px = power(memo, x);
                        const int py = power(memo, y);

                        if (px == py) return x < y;
                        return px < py;
                    });

        return xs[k - 1];
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Power of 7 and 8") {
        unordered_map<int, int> memo;
        int actual = power(memo, 7);
        int expected = 16;
        EXPECT(actual == expected);

        actual = power(memo, 8);
        expected = 3;
        EXPECT(actual == expected);
    },
    CASE("Power of 14") {
        unordered_map<int, int> memo;
        const int actual = power(memo, 14);
        const int expected = 17;
        EXPECT(actual == expected);
    },
    CASE("Power of 15") {
        unordered_map<int, int> memo;
        const int actual = power(memo, 15);
        const int expected = 17;
        EXPECT(actual == expected);
    },
    CASE("Power of 12") {
        unordered_map<int, int> memo;
        const int actual = power(memo, 12);
        const int expected = 9;
        EXPECT(actual == expected);
    },
    CASE("Power of 1") {
        unordered_map<int, int> memo;
        const int actual = power(memo, 1);
        const int expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Power of 13") {
        unordered_map<int, int> memo;
        const int actual = power(memo, 13);
        const int expected = 9;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = Solution{}.getKth(12, 15, 2);
        const auto expected = 13;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = Solution{}.getKth(1, 1, 1);
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = Solution{}.getKth(7, 11, 4);
        const auto expected = 7;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = Solution{}.getKth(10, 20, 5);
        const auto expected = 13;
        EXPECT(actual == expected);
    },
    CASE("Example 5") {
        const auto actual = Solution{}.getKth(1, 1000, 777);
        const auto expected = 570;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
