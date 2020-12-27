#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int intof(const T x) {
    return static_cast<int>(x);
}

struct DivideLoot final {
    string verify(const int n, vector<int> xs) const {
        while (intof(xs.size()) < 2 * n) xs.push_back(0);
        sort(begin(xs), end(xs));

        set<int> ys;
        for (int i = 0; i < n; ++i) {
            ys.insert(xs[n - 1 - i] + xs[n + i]);
        }

        return ys.size() == 1U ? "possible" : "impossible";
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = DivideLoot{}.verify(1, {47});
        const auto expected = "possible";
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = DivideLoot{}.verify(3, {10, 8, 10, 1, 1});
        const auto expected = "impossible";
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = DivideLoot{}.verify(3, {3, 9, 10, 7, 1});
        const auto expected = "possible";
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = DivideLoot{}.verify(6, {1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1});
        const auto expected = "possible";
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = DivideLoot{}.verify(2, {40, 1, 42});
        const auto expected = "impossible";
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
