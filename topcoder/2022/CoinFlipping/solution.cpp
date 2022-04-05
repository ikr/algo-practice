#include "lest.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
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

char flip_char(const char x) {
    if (x == 'T') return 'H';
    if (x == 'H') return 'T';
    assert(x == '.');
    return x;
}

string flip_str(string xs) {
    transform(xbegin(xs), xend(xs), begin(xs), flip_char);
    return xs;
}

vector<string> flip_row(vector<string> grid, const int ro) {
    assert(0 <= ro && ro < sz(grid));
    grid[ro] = flip_str(grid[ro]);
    return grid;
}

struct CoinFlipping final {
    int mostHeads(const vector<string> &grid) const {
        assert(!grid.empty());
        return 42;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = CoinFlipping{}.mostHeads({"H.T.H", "TTTTT", "HHTHH"});
        const auto expected = 12;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = CoinFlipping{}.mostHeads({"TT", "HT"});
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = CoinFlipping{}.mostHeads({"T....", "...T.", "..T..", "....T", ".T..."});
        const auto expected = 5;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = CoinFlipping{}.mostHeads({"HT.HT.HT.HT.", ".HT.HT.HT.HT", "T.HT.HT.HT.H"});
        const auto expected = 20;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
