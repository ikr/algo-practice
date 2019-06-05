#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using Row = vector<int>;
using Board = vector<vector<int>>;
using RowCol = pair<int, int>;

template <typename T> int intof(T x) { return static_cast<int>(x); }

RowCol operator+(const RowCol p1, const RowCol p2) {
    return make_pair(p1.first + p2.first, p1.second + p2.second);
}

constexpr int sz_rows = 3;
constexpr int sz_cols = 2;

void assert_board(const Board &board) {
    assert(board.size() == sz_rows);

    Row all;
    for (const auto &r : board) {
        assert(r.size() == sz_cols);
        all.insert(all.end(), r.begin(), r.end());
    }
    sort(all.begin(), all.end());

    Row expected(sz_rows * sz_cols);
    iota(expected.begin(), expected.end(), 0);

    assert(all == expected);
}

void assert_rowcol(const RowCol &p) {
    assert(p.first >= 0);
    assert(p.first < sz_rows);
    assert(p.second >= 0);
    assert(p.second < sz_cols);
}

void assert_neighs(const RowCol &p1, const RowCol &p2) {
    assert(p1 != p2);
    assert(abs(p1.first - p2.first) == 1 || abs(p1.second - p2.second) == 1);
    assert(p1.first == p2.first || p1.second == p2.second);
}

Board swap_neighs(Board board, const RowCol &p1, const RowCol &p2) {
    assert_board(board);
    assert_rowcol(p1);
    assert_rowcol(p2);
    assert_neighs(p1, p2);
    assert(board[p1.first][p1.second] = 0 || board[p2.first][p2.second] == 0);

    swap(board[p1.first][p1.second], board[p2.first][p2.second]);
    return board;
}

RowCol locate_zero(const Board &board) {
    assert_board(board);

    for (int r = 0; r != sz_rows; ++r)
        for (int c = 0; c != sz_cols; ++c)
            if (board[r][c] == 0) return make_pair(r, c);

    throw logic_error("No zero located");
}

vector<RowCol> adjacent(const RowCol &p) {
    vector<RowCol> result{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    transform(result.begin(), result.end(), result.begin(),
              [p](const RowCol &delta) { return p + delta; });

    result.erase(remove_if(result.begin(), result.end(),
                           [](const RowCol &q) {
                               return q.first < 0 || q.second < 0 ||
                                      q.first >= sz_rows || q.second >= sz_cols;
                           }),
                 result.end());

    return result;
}

vector<Board> adjacent(const Board &board) {
    const RowCol p_zero = locate_zero(board);
    vector<Board> result;

    for (const auto p : adjacent(p_zero)) {
        result.push_back(swap_neighs(board, p_zero, p));
    }

    return result;
}

struct Solution final {
    int slidingPuzzle(const Board &board) const { return intof(board.size()); }
};

// clang-format off
const lest::test tests[] = {
    CASE("problem statement example 1") {
        const auto actual = Solution().slidingPuzzle({
            {1,2,3},
            {4,0,5}
        });

        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("problem statement example 1 variation") {
        const auto actual = Solution().slidingPuzzle({
            {1,2,0},
            {4,5,3}
        });

        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("problem statement example 2") {
        const auto actual = Solution().slidingPuzzle({
            {1,2,3},
            {5,4,0}
        });

        const auto expected = -1;
        EXPECT(actual == expected);
    },
    CASE("problem statement example 3") {
        const auto actual = Solution().slidingPuzzle({
            {4,1,2},
            {5,0,3}
        });

        const auto expected = 5;
        EXPECT(actual == expected);
    },
    CASE("problem statement example 4") {
        const auto actual = Solution().slidingPuzzle({
            {3,2,4},
            {1,5,0}
        });

        const auto expected = 14;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
