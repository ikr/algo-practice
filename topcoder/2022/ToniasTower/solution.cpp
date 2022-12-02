#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

struct ToniasTower final {
    vector<int> build(const int N) const {
        ll b = 1LL;
        while ((b + 1LL) * (b + 2LL) / 2LL <= N) ++b;

        const ll q = b * (b + 1LL) / 2LL;
        const auto r = N - inof(q);

        vector<int> result(b);
        iota(begin(result), end(result), 1);
        result.back() += r;

        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = ToniasTower{}.build(1);
        const auto expected = vector<int>{1};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = ToniasTower{}.build(15);
        const auto expected = vector<int>{1, 2, 3, 4, 5};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
