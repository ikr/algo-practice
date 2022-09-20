#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

pll fr_reduce(pll nd) {
    const auto g = __gcd(nd.first, nd.second);
    nd.first /= g;
    nd.second /= g;
    return nd;
}

pll fr_half(pll nd) {
    nd.second *= 2L;
    return fr_reduce(nd);
}

pll fr_plus(pll nd1, pll nd2) {
    const auto g = __gcd(nd1.second, nd2.second);
    const auto k1 = nd1.second / g;
    const auto k2 = nd2.second / g;

    return fr_reduce({k2 * nd1.first + k1 * nd2.first, k1 * k2 * g});
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
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

struct ThreeFractions final {
    vector<int> find(const int N1, const int D1, const int N2,
                     const int D2) const {
        const auto nd1 = fr_reduce({N1, D1});
        const auto nd2 = fr_reduce({N2, D2});
        const auto CD = fr_half(fr_plus(nd1, nd2));
        const auto AB = fr_half(fr_plus(nd1, CD));
        const auto EF = fr_half(fr_plus(CD, nd2));
        return {inof(AB.first),  inof(AB.second), inof(CD.first),
                inof(CD.second), inof(EF.first),  inof(EF.second)};
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = ThreeFractions{}.find(1, 3, 2, 3);
        const auto expected = vector<int>{1, 2, 3, 5, 147, 233};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = ThreeFractions{}.find(1, 7, 7, 1);
        const auto expected = vector<int>{2, 1, 5, 1, 3, 1};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
