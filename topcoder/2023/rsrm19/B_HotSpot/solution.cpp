#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

struct HotSpot final {
    double bestPoint(const vector<int> &xs) const {
        const auto s = accumulate(cbegin(xs), cend(xs), 0.0, plus<double>{});
        return s / doof(sz(xs));
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = HotSpot{}.bestPoint({1, 5});
        const auto expected = 3.0;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = HotSpot{}.bestPoint({5});
        const auto expected = 5.0;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
