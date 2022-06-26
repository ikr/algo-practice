#include "lest.hpp"
#include <iostream>
#include <vector>
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

vector<int> months(const bool leap) {
    return leap ? vector<int>{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
                : vector<int>{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
}

struct FridayTheThirteenth final {
    vector<int> count(const int z, const int leap) const {
        vector<int> result(12, 0);
        const auto ms = months(leap);
        for (int m = 0, wd = z; m < sz(ms); ++m) {
            for (int d = 1; d <= ms[m]; ++d) {
                if (d == 13 && wd == 5) ++result[m];

                ++wd;
                wd %= 7;
            }
        }

        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = FridayTheThirteenth{}.count(6, 0);
        const auto expected = vector<int>{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = FridayTheThirteenth{}.count(0, 0);
        const auto expected = vector<int> {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
