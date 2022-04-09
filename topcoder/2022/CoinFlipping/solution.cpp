#include "lest.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
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

void flip_str(string &xs) {
    transform(xbegin(xs), xend(xs), begin(xs), flip_char);
}

void flip_row(vector<string> &grid, const int ro) {
    assert(0 <= ro && ro < sz(grid));
    flip_str(grid[ro]);
}

void flip_col(vector<string> &grid, const int co) {
    assert(0 <= co && co < sz(grid[0]));
    for (int ro = 0; ro < sz(grid); ++ro) {
        grid[ro][co] = flip_char(grid[ro][co]);
    }
}

int total_heads(const vector<string> &grid) {
    return accumulate(xbegin(grid), xend(grid), 0,
                      [](const int agg, const auto &row) {
                          return agg + inof(count(xbegin(row), xend(row), 'H'));
                      });
}

int count_in_col(const char x, const vector<string> &grid, const int co) {
    int result{};
    for (int ro = 0; ro < sz(grid); ++ro) {
        result += grid[ro][co] == x;
    }
    return result;
}

struct CoinFlipping final {
    int mostHeads(const vector<string> &grid) const {
        const auto H = sz(grid);
        const auto W = sz(grid[0]);
        int result{};

        for (int ro_bits = 0; ro_bits < (1 << H); ++ro_bits) {
            auto g = grid;
            for (int ro = 0; ro < H; ++ro) {
                if ((1 << ro) & ro_bits) {
                    flip_row(g, ro);
                }
            }
            const auto baseline = total_heads(g);
            result = max(result, baseline);

            for (int co = 0; co < W; ++co) {
                flip_col(g, co);

                const auto H = count_in_col('H', g, co);
                const auto T = count_in_col('T', g, co);

                if (T > H) {
                    // TODO
                }

                flip_col(g, co);
            }
        }

        return result;
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
