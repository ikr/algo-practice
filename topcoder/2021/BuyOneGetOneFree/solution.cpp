#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

struct BuyOneGetOneFree final {
    int buy(vector<int> xs) const {
        const int n = xs.size();
        sort(rbegin(xs), rend(xs));

        int ans = 0;
        for (int i = 0; i + 1 < n; i += 2) ans += xs[i];
        if (n % 2) ans += xs.back();
        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = BuyOneGetOneFree{}.buy({47});
        const auto expected = 47;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = BuyOneGetOneFree{}.buy({10, 20});
        const auto expected = 20;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = BuyOneGetOneFree{}.buy({10, 20, 30, 20});
        const auto expected = 50;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = BuyOneGetOneFree{}.buy({5, 7, 13, 2, 9});
        const auto expected = 22;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = BuyOneGetOneFree{}.buy({100, 100, 100, 100, 100, 100});
        const auto expected = 300;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
