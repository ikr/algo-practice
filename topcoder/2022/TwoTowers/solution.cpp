#include "lest.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
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

using pii = pair<int, int>;

struct TwoTowers final {
    int maxDifference(const vector<int> &A, const vector<int> &B) const {
        vector<pii> ps(sz(A));

        transform(xbegin(A), xend(A), xbegin(B), begin(ps),
                  [](const int a, const int b) -> pii {
                      return pii{min(a, b), max(a, b)};
                  });

        return accumulate(
                   xbegin(ps), xend(ps), 0,
                   [](const int agg, const pii p) { return agg + p.second; }) -
               accumulate(
                   xbegin(ps), xend(ps), 0,
                   [](const int agg, const pii p) { return agg + p.first; });
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = TwoTowers{}.maxDifference(vector<int>{3}, vector<int>{5});
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = TwoTowers{}.maxDifference(vector<int>{5, 4, 1}, vector<int>{3, 4, 9});
        const auto expected = 10;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
