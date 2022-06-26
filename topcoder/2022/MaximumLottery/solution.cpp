#include "lest.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

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

struct MaximumLottery final {
    double ticketPrice(const vector<int> &xs, const int k) const {
        const auto n = sz(xs);
        auto ys = xs;
        sort(begin(ys), end(ys));
        const auto coef = doof(k) / doof(n);
        const auto d = ys.back() - ys[k - 1];

        return doof(ys[k - 1]) + d * coef;
    }
};

static constexpr double EPS = 0.000001;

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = MaximumLottery{}.ticketPrice({10, 10, 10, 10, 10, 10, 10}, 3);
        const auto expected = 10.0;
        EXPECT(abs(actual - expected) < EPS);
    },
    CASE("Example 1") {
        const auto actual = MaximumLottery{}.ticketPrice({10, 50, 40, 20, 30}, 5);
        const auto expected = 50.0;
        EXPECT(abs(actual - expected) < EPS);
    },
    CASE("Example 2") {
        const auto actual = MaximumLottery{}.ticketPrice({11, 12, 13, 14}, 3);
        const auto expected = 13.75;
        EXPECT(abs(actual - expected) < EPS);
    },
    CASE("Example 3") {
        const auto actual = MaximumLottery{}.ticketPrice({11, 12, 13, 14, 15, 16, 18}, 1);
        const auto expected = 14.142857142857142;
        EXPECT(abs(actual - expected) < EPS);
    },
    CASE("Example 4") {
        const auto actual = MaximumLottery{}.ticketPrice({1, 1, 2, 3, 5, 8, 13, 21}, 4);
        const auto expected = 15.685714285714285;
        EXPECT(abs(actual - expected) < EPS);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
