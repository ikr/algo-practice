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

struct OxToTiger final {
    string rewrite(string xs) const {
        const auto n = sz(xs);
        if (n < 2) return xs;
        if (xs == "ox") return "tiger";
        if (n < 3) return xs;

        if (xs[n - 3] == ' ' && xs[n - 2] == 'o' && xs[n - 1] == 'x') {
            xs = xs.substr(0, n - 3) + " tiger";
        }

        if (xs[0] == 'o' && xs[1] == 'x' && xs[2] == ' ') {
            xs = "tiger " + xs.substr(3);
        }

        auto i = xs.find(" ox ");
        while (i != xs.npos) {
            const auto pre = xs.substr(0, i);
            const auto post = xs.substr(i + 4);
            xs = pre + " tiger " + post;
            i = xs.find(" ox ", i);
        }

        return xs;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = OxToTiger{}.rewrite("ox");
        const auto expected = "tiger";
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = OxToTiger{}.rewrite("fox");
        const auto expected = "fox";
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = OxToTiger{}.rewrite(" ox ");
        const auto expected = " tiger ";
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = OxToTiger{}.rewrite("the ox the ox the ox and the fox in the box");
        const auto expected = "the tiger the tiger the tiger and the fox in the box";
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = OxToTiger{}.rewrite("the plural of ox is oxen");
        const auto expected = "the plural of tiger is oxen";
        EXPECT(actual == expected);
    },
    CASE("Example A") {
        const auto actual = OxToTiger{}.rewrite(" ox");
        const auto expected = " tiger";
        EXPECT(actual == expected);
    },
    CASE("Example B") {
        const auto actual = OxToTiger{}.rewrite("ox ");
        const auto expected = "tiger ";
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
