#include "lest.hpp"
#include <bits/stdc++.h>
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

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int total_costs(const vector<int> &ts, const int mth, const int cll, const int mnt) {
    int result = mth + sz(ts) * cll;

    for (const auto t : ts) {
        result += mnt * div_ceil(t, 60);
    }

    return result;
}

struct CellPhoneService final {
    int payLeast(const vector<int> &ts, const int P, const vector<int> &mth,
                 const vector<int> &cll, const vector<int> &mnt) const {
        vector<int> ttl(P);
        for (int i = 0; i < P; ++i) {
            ttl[i] = total_costs(ts, mth[i], cll[i], mnt[i]);
        }
        return *min_element(xbegin(ttl), xend(ttl));
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = CellPhoneService{}.payLeast();
        const auto expected = 42;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = CellPhoneService{}.payLeast();
        const auto expected = 42;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
