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

struct JumpingTiger final {
    int travel(const vector<string> &grid) const { return 42; }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = JumpingTiger{}.travel({"T.######", "#..#####", "##..####", "###..###", "####..##", "#####..#", "######..", "#######L"});
        const auto expected = 14;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = JumpingTiger{}.travel({"T.######", "#..#####", "##..####", "###..###", "####..##", "#####..#", "######..", ".######L"});
        const auto expected = 14;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = JumpingTiger{}.travel({"T.######", "#..#####", "##..####", "###..###", "####..##", "#####..#", ".#####..", ".######L"});
        const auto expected = 6;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = JumpingTiger{}.travel({"T.######", "#..#####", "##..####", "###..###", "####..##", "#####..#", ".#####..", ".#####.L"});
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = JumpingTiger{}.travel({".##.", "#L##", "####", ".#T#"});
        const auto expected = -1;
        EXPECT(actual == expected);
    },
    CASE("Example 5") {
        const auto actual = JumpingTiger{}.travel({"T", "#", "#", "L", "#", "#", ".", "."});
        const auto expected = -1;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
