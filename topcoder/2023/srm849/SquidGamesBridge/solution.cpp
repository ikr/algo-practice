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

namespace kactl { // https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/Eratosthenes.h
#define rep(i, a, b) for (int i = a; i < (b); ++i)
constexpr int MAX_PR = 10'000'000;
static bitset<MAX_PR> isprime;
vector<int> eratosthenes_sieve(const int lim) {
    isprime.set();
    isprime[0] = isprime[1] = 0;
    for (int i = 4; i < lim; i += 2) isprime[i] = 0;
    for (int i = 3; i * i < lim; i += 2)
        if (isprime[i])
            for (int j = i * i; j < lim; j += i * 2) isprime[j] = 0;
    vector<int> pr;
    rep(i, 2, lim) if (isprime[i]) pr.push_back(i);
    return pr;
}
} // namespace kactl

static const auto Ps = []() -> vector<int> {
    return kactl::eratosthenes_sieve(1'000'000);
}();

struct SquidGamesBridge final {
    int cross(int P, const int S) const {
        const auto for_sure = max(0, P - S);
        P -= for_sure;

        const auto lefts =
            inof(lower_bound(xbegin(Ps), xend(Ps), P) - xbegin(Ps));
        const auto even_fell = P / 2 - lefts;
        const auto odd_fell = P / 2 - (P - lefts);

        return for_sure + (P - even_fell - odd_fell);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = SquidGamesBridge{}.cross(3, 2);
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = SquidGamesBridge{}.cross(3, 4);
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = SquidGamesBridge{}.cross(3, 5);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = SquidGamesBridge{}.cross(1234567, 1);
        const auto expected = 1234566;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = SquidGamesBridge{}.cross(1234, 567);
        const auto expected = 1029;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
