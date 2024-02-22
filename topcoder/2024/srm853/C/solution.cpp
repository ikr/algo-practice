#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

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

vector<int> generate_L(const int T, const int M, const int C,
                       const vector<int> &Lprefix, const int seed) {
    ll state = seed;
    const auto PL = sz(Lprefix);

    vector<int> L(T, 0);
    for (int i = 0; i < PL; ++i) {
        L[i] = Lprefix[i];
    }

    for (int i = PL; i < T; ++i) {
        if (C == 1 && i > 0) {
            state = (state * 1103515245 + 12345LL) % (1LL << 31);
            auto old = L[state % i];
            state = (state * 1103515245 + 12345LL) % (1LL << 31);
            auto spread = (state % 21LL) - 10LL;
            L[i] = inof(max(0LL, min(M - 1LL, old + spread)));
        } else {
            state = (state * 1103515245 + 12345) % (1LL << 31);
            L[i] = inof((state % (0LL + M)));
        }
    }
    return L;
}

struct CollectTrash final {
    int solve_it(const int P, const int T, const int M, const int C,
                 const vector<int> &Lprefix, const int seed) const {
        const auto L = generate_L(T, M, C, Lprefix, seed);
        // tbd
        return 42;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = CollectTrash{}.solve_it(1, 4, 1000000000, 0, {7, 4, 10, 4}, 1000000000);
        const auto expected = 14;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = CollectTrash{}.solve_it(47, 47003, 1, 0, {}, 47);
        const auto expected = 1001;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = CollectTrash{}.solve_it(2, 5, 100000, 0, {1, 2, 3, 4, 5}, 42);
        const auto expected = 7;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = CollectTrash{}.solve_it(3, 12, 7654321, 0, {1000, 2000, 3000}, 1234567);
        const auto expected = 5937965;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = CollectTrash{}.solve_it(3, 12, 7654321, 1, {1000, 2000, 3000}, 1234567);
        const auto expected = 3015;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
