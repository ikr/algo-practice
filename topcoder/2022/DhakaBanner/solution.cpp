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

struct DhakaBanner final {
    int edit(const string &xs_) const {
        const auto N_ = sz(xs_);

        string xs = string(N_, '.') + xs_;
        const auto N = sz(xs);

        const auto at = [&xs](const int i) -> char {
            if (i < 0 || i >= sz(xs)) return '.';
            return xs[i];
        };

        int result{INT_MAX};
        for (int i0 = 0; i0 < N; ++i0) {
            for (int k = 1; k <= (N / 2 + 2); ++k) {
                int cur = N_;
                if (N_ < 5) cur = 5;

                cur -= at(i0) == 'D';
                cur -= at(i0 + k) == 'H';
                cur -= at(i0 + 2 * k) == 'A';
                cur -= at(i0 + 3 * k) == 'K';
                cur -= at(i0 + 4 * k) == 'A';

                result = min(result, cur);
            }
        }
        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = DhakaBanner{}.edit("DHAKA");
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = DhakaBanner{}.edit("WELCOMETODHAKABANGLADESH");
        const auto expected = 19;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = DhakaBanner{}.edit("AA");
        const auto expected = 5;
        EXPECT(actual == expected);
    },
    CASE("Example 6") {
        const auto actual = DhakaBanner{}.edit("TOPCODER");
        const auto expected = 11;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
