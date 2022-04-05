#include "lest.hpp"
#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

using ll = long long;

struct HouseOfCards final {
    ll count(const int N) const {
        const ll n = N;
        const auto b = (n * n + n) / 2LL;
        const auto s = (n * n - n) / 2LL;
        return 2LL * b + s;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = HouseOfCards{}.count(1);
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = HouseOfCards{}.count(2);
        const auto expected = 7;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
