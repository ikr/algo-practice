#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

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

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

struct ProbabilisticStreamMinimum final {
    double calculate(const int N, const int K) const {
        assert(N > 0);
        auto agg = 0.0;

        for (int i = 1; i <= K - 1; ++i) {
            agg += doof(K - i) / doof(K * K);
        }

        return agg;
    }
};

static constexpr auto EPS = 0.000000001;

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = ProbabilisticStreamMinimum{}.calculate(47, 1);
        const auto expected = 1.0;
        EXPECT(abs(actual - expected) < EPS);
    },
    CASE("Example 1") {
        const auto actual = ProbabilisticStreamMinimum{}.calculate(3, 3);
        const auto expected = 0.691358024691358;
        EXPECT(abs(actual - expected) < EPS);
    },
    CASE("Example 2") {
        const auto actual = ProbabilisticStreamMinimum{}.calculate(20, 4);
        const auto expected = 0.66650390625;
        EXPECT(abs(actual - expected) < EPS);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
