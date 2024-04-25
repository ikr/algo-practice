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

const string Yes{"possible"};
const string No{"impossible"};

struct EqualizeBags final {
    string check(const int n, const vector<int> &xs, int e) const {
        assert(sz(xs) == n);
        if (n == 1) return xs[0] >= e ? Yes : No;

        const auto lo = *min_element(xbegin(xs), xend(xs));
        int first_cut{};
        for (const auto &x : xs) {
            first_cut += x - lo;
        }
        if (first_cut > e) return No;
        e -= first_cut;
        if (e == 0) return Yes;

        const auto remaining = n * lo;
        return (remaining >= e) && (e % n == 0) ? Yes : No;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = EqualizeBags{}.check(3, {5,47,5}, 42);
        const auto expected = Yes;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = EqualizeBags{}.check(3, {5, 47, 5}, 43);
        const auto expected = No;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
