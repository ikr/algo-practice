#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Placement = array<int, 2>;
static constexpr int M = 4;

string representation(const Placement &p) {
    const auto div = [&]() -> string {
        switch (p[0]) {
        case 0:
            return "Platinum";
        case 1:
            return "Gold";
        case 2:
            return "Silver";
        default:
            assert(p[0] == 3);
            return "Bronze";
        }
    }();

    return div + " " + to_string(p[1] + 1);
}

Placement placement_of(const int code) {
    assert(code < M * M);
    return {code / M, code % M};
}

struct RankUp final {
    string level(const string &xs) const {
        int code = M * M - 1;
        int s{};

        for (int i = 0; i < sz(xs); ++i) {
            if (xs[i] == 'W') {
                s = min(5, s + 2);
                if (s == 5 && i >= 2 && xs.substr(i - 2, 3) == "WWW" &&
                    code > 0) {
                    --code;
                    s = 0;
                }
            } else {
                assert(xs[i] == 'L');
                s = max(0, s - 1);
                if (s == 0 && i >= 2 && xs.substr(i - 2, 3) == "LLL" &&
                    code < M * M - 1 && (code / M) == (code + 1) / M) {
                    ++code;
                    s = 5;
                }
            }
        }

        return representation(placement_of(code));
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = RankUp{}.level("LLLLL");
        const auto expected = string{"Bronze 4"};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = RankUp{}.level("WWLWW");
        const auto expected = string{"Bronze 4"};
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = RankUp{}.level("WWLLWWW");
        const auto expected = string{"Bronze 3"};
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = RankUp{}.level("WWWLLL");
        const auto expected = string{"Bronze 4"};
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = RankUp{}.level("WWWWWWWWWWWWWLLL");
        const auto expected = string{"Silver 4"};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
