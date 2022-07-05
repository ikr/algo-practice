#include "lest.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> vector<vector<T>> precompute_binomials(const int maxn) {
    vector<vector<T>> C(maxn + 1, vector<T>(maxn + 1, 0));
    C[0][0] = 1;

    for (int n = 1; n <= maxn; ++n) {
        C[n][0] = 1;
        C[n][n] = 1;
        for (int k = 1; k < n; ++k) {
            C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
        }
    }

    return C;
}

struct MaximumLottery final {
    double ticketPrice(vector<int> xs, const int k) const {
        const auto n = sz(xs);
        const auto C = precompute_binomials<long double>(n);
        sort(begin(xs), end(xs));

        long double result = 0;
        for (int i = k; i <= n; ++i) {
            result += 1.0 * xs[i - 1] * C[i - 1][k - 1];
        }
        return static_cast<double>(result / C[n][k]);
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
