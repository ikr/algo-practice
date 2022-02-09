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

struct OddSum final {
    int getSum(const vi &xs) const {
        int ans{};
        for (const auto x : xs) {
            if (x % 2) ans += x;
        }
        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = OddSum{}.getSum({ 1, 2, 3 });
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = OddSum{}.getSum({ 2, 4, 6 });
        const auto expected = 0;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
