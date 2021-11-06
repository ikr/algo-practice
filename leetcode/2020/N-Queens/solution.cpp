#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

namespace {
template <typename T> int intof(const T x) { return static_cast<int>(x); }

using Board = vector<string>;
using RowCol = pair<int, int>;

struct SolutionPart final {
    explicit SolutionPart(const int board_size)
        : m_board_size{board_size}, m_queens{}, m_columns(board_size, false),
          m_slash_diagonals(2 * board_size, false),
          m_backslash_diagonals(2 * board_size, false) {}

    bool place_queen(const RowCol sq) {
        assert(m_queens.empty() || sq.first == m_queens.back().first + 1);

        if (m_columns[sq.second] || m_slash_diagonals[slash_index(sq)] ||
            m_backslash_diagonals[backslash_index(sq)]) {
            return false;
        }

        m_queens.push_back(sq);
        m_columns[sq.second] = true;
        m_slash_diagonals[slash_index(sq)] = true;
        m_backslash_diagonals[backslash_index(sq)] = true;

        return true;
    }

    void remove_last_queen() {
        assert(!m_queens.empty());

        const auto sq = m_queens.back();

        m_queens.pop_back();
        m_columns[sq.second] = false;
        m_slash_diagonals[slash_index(sq)] = false;
        m_backslash_diagonals[backslash_index(sq)] = false;
    }

    Board capture() const {
        Board ans(m_board_size, string(m_board_size, '.'));

        for (const auto [r, c] : m_queens) {
            ans[r][c] = 'Q';
        }

        return ans;
    }

    bool is_complete() const { return intof(m_queens.size()) == m_board_size; }

    int next_row_index() const {
        return m_queens.empty() ? 0 : m_queens.back().first + 1;
    }

    int board_size() const { return m_board_size; }

  private:
    int slash_index(const RowCol sq) const {
        const auto [r, c] = sq;
        return 2 * (m_board_size - 1) - (r + c);
    }

    int backslash_index(const RowCol sq) const {
        const auto [r, c] = sq;
        return r - c + (m_board_size - 1);
    }

    const int m_board_size;
    vector<RowCol> m_queens;
    vector<bool> m_columns;
    vector<bool> m_slash_diagonals;
    vector<bool> m_backslash_diagonals;
};

void find_solutions(vector<Board> &ans, SolutionPart &partial) {
    if (partial.is_complete()) {
        ans.push_back(partial.capture());
        return;
    }

    const int r = partial.next_row_index();

    for (int c = 0; c != partial.board_size(); ++c) {
        if (partial.place_queen({r, c})) {
            find_solutions(ans, partial);
            partial.remove_last_queen();
        }
    }
}
} // namespace

struct Solution final {
    vector<Board> solveNQueens(const int n) const {
        vector<Board> ans;
        SolutionPart partial{n};
        find_solutions(ans, partial);
        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("1 x 1") {
        const auto actual = Solution{}.solveNQueens(1).size();
        const auto expected = 1U;
        EXPECT(actual == expected);
    },
    CASE("2 x 2") {
        const auto actual = Solution{}.solveNQueens(2).size();
        const auto expected = 0U;
        EXPECT(actual == expected);
    },
    CASE("3 x 3") {
        const auto actual = Solution{}.solveNQueens(3).size();
        const auto expected = 0U;
        EXPECT(actual == expected);
    },
    CASE("4 x 4") {
        const auto actual = Solution{}.solveNQueens(4).size();
        const auto expected = 2U;
        EXPECT(actual == expected);
    },
    CASE("5 x 5") {
        const auto actual = Solution{}.solveNQueens(5).size();
        const auto expected = 10U;
        EXPECT(actual == expected);
    },
    CASE("9 x 9") {
        const auto actual = Solution{}.solveNQueens(9).size();
        const auto expected = 352U;
        EXPECT(actual == expected);
    },
    CASE("10 x 10") {
        const auto actual = Solution{}.solveNQueens(10).size();
        const auto expected = 724U;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
