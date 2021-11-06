#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using Row = vector<int>;
using Board = vector<vector<int>>;
using RowCol = pair<int, int>;

constexpr int sz_rows = 2;
constexpr int sz_cols = 3;

RowCol operator+(const RowCol p1, const RowCol p2) {
    return make_pair(p1.first + p2.first, p1.second + p2.second);
}

int board_hash(const Board &board) {
    int result{0};
    bool initialized{false};

    for (const auto &r : board) {
        for (const auto &c : r) {
            if (!initialized) {
                result = c;
                initialized = true;
                continue;
            }

            result = 31 * result + c;
        }
    }

    return result;
}

Board swap_neighs(Board board, const RowCol &p1, const RowCol &p2) {
    swap(board[p1.first][p1.second], board[p2.first][p2.second]);
    return board;
}

RowCol locate_zero(const Board &board) {
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

Board goal() {
    Row src(sz_rows * sz_cols);
    iota(src.begin(), src.end() - 1, 1);
    src.back() = 0;

    Board result;

    for (int i = 0; i != sz_rows; ++i) {
        Row row(src.begin() + (i * sz_cols),
                src.begin() + (i * sz_cols + sz_cols));

        result.push_back(row);
    }

    return result;
}

struct Solution final {
    int slidingPuzzle(const Board &board) const {
        const auto g = goal();
        if (g == board) return 0;

        queue<Board> boards_q;
        unordered_set<int> seen_hashes;
        unordered_map<int, int> distances_by_hash;

        boards_q.push(board);
        distances_by_hash[board_hash(board)] = 0;

        while (!boards_q.empty()) {
            const auto x = boards_q.front();
            boards_q.pop();

            const int distance_to_x = distances_by_hash.at(board_hash(x));
            for (const auto a : adjacent(x)) {
                if (a == g) return distance_to_x + 1;

                const int h = board_hash(a);
                if (!seen_hashes.count(h)) {
                    boards_q.push(a);
                    distances_by_hash[h] = distance_to_x + 1;
                    seen_hashes.insert(h);
                }
            }
        }

        return -1;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("trivial") {
        const auto actual = Solution().slidingPuzzle({
            {1,2,3},
            {4,5,0}
        });

        const auto expected = 0;
        EXPECT(actual == expected);
    },
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
