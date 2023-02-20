#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

enum class Answer { WHITE_IN_CHECK, BLACK_IN_CHECK, NONE_IN_CHECK };

using Row = array<char, 8>;
using Rows = array<Row, 8>;

using Coord = complex<int>;
constexpr int c_ro(const Coord coord) { return coord.real(); }
constexpr int c_co(const Coord coord) { return coord.imag(); }

string next_line() {
    string ans;
    getline(cin, ans);
    return ans;
}

Row line_to_row(const string &line) {
    Row ans;
    copy(line.cbegin(), line.cend(), begin(ans));
    return ans;
}

Rows read_board() {
    Rows ans;
    for (auto &row : ans) {
        row = line_to_row(next_line());
    }
    return ans;
}

bool is_empty_board(const Rows &board) {
    return all_of(board.cbegin(), board.cend(), [](const Row &row) {
        return all_of(row.cbegin(), row.cend(),
                      [](const char c) { return c == '.'; });
    });
}

string format_answer(const int game, const Answer answer) {
    const auto answer_key = [answer]() -> string {
        switch (answer) {
        case Answer::WHITE_IN_CHECK:
            return "white";
        case Answer::BLACK_IN_CHECK:
            return "black";
        default:
            return "no";
        }
    };

    stringstream ss;
    ss << "Game #" << game << ": " << answer_key() << " king is in check.";
    return ss.str();
}

constexpr bool in_bounds(const Coord coord) {
    return c_ro(coord) >= 0 && c_ro(coord) < 8 && c_co(coord) >= 0 &&
           c_co(coord) < 8;
}

bool is_at(const Rows &board, const Coord coord, const char piece) {
    if (!in_bounds(coord)) return false;
    return board[c_ro(coord)][c_co(coord)] == piece;
}

bool check_by_white_pawn(const Rows &board, const Coord coord) {
    return is_at(board, coord + Coord{-1, -1}, 'k') ||
           is_at(board, coord + Coord{-1, 1}, 'k');
}

bool check_by_black_pawn(const Rows &board, const Coord coord) {
    return is_at(board, coord + Coord{1, -1}, 'K') ||
           is_at(board, coord + Coord{1, 1}, 'K');
}

bool check_by_knight(const Rows &board, const char king, const Coord coord) {
    const vector<Coord> deltas{{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2},
                               {1, -2},  {2, -1},  {2, 1},  {1, 2}};
    for (const auto &d : deltas) {
        if (is_at(board, coord + d, king)) return true;
    }
    return false;
}

bool check_by_long_ranger(const Rows &board, const char king, const Coord coord,
                          const vector<Coord> &directoins) {
    for (const auto dir : directoins) {
        auto curr = coord + dir;
        while (is_at(board, curr, '.')) curr += dir;
        if (is_at(board, curr, king)) return true;
    }

    return false;
}

vector<Coord> straight_directions() {
    return {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
}

vector<Coord> diagonal_directions() {
    return {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
}

template <typename T> vector<T> concatenate(vector<T> xs, const vector<T> &ys) {
    xs.insert(end(xs), ys.cbegin(), ys.cend());
    return xs;
}

vector<Coord> all_directions() {
    return concatenate(straight_directions(), diagonal_directions());
}

Answer assess_board(const Rows &board) {
    for (int ro = 0; ro < 8; ++ro) {
        for (int co = 0; co < 8; ++co) {
            const Coord coord{ro, co};

            switch (board[ro][co]) {
            case 'P':
                if (check_by_white_pawn(board, coord))
                    return Answer::BLACK_IN_CHECK;
                break;
            case 'p':
                if (check_by_black_pawn(board, coord))
                    return Answer::WHITE_IN_CHECK;
                break;
            case 'N':
                if (check_by_knight(board, 'k', coord))
                    return Answer::BLACK_IN_CHECK;
                break;
            case 'n':
                if (check_by_knight(board, 'K', coord))
                    return Answer::WHITE_IN_CHECK;
                break;
            case 'R':
                if (check_by_long_ranger(board, 'k', coord,
                                         straight_directions()))
                    return Answer::BLACK_IN_CHECK;
                break;
            case 'r':
                if (check_by_long_ranger(board, 'K', coord,
                                         straight_directions()))
                    return Answer::WHITE_IN_CHECK;
                break;
            case 'B':
                if (check_by_long_ranger(board, 'k', coord,
                                         diagonal_directions()))
                    return Answer::BLACK_IN_CHECK;
                break;
            case 'b':
                if (check_by_long_ranger(board, 'K', coord,
                                         diagonal_directions()))
                    return Answer::WHITE_IN_CHECK;
                break;
            case 'Q':
                if (check_by_long_ranger(board, 'k', coord, all_directions()))
                    return Answer::BLACK_IN_CHECK;
                break;
            case 'q':
                if (check_by_long_ranger(board, 'K', coord, all_directions()))
                    return Answer::WHITE_IN_CHECK;
                break;
            }
        }
    }

    return Answer::NONE_IN_CHECK;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    vector<Rows> boards;
    for (;;) {
        if (!boards.empty()) next_line();
        boards.push_back(read_board());

        if (is_empty_board(boards.back())) {
            boards.pop_back();
            break;
        }
    }

    for (int i = 0; i < sz(boards); ++i) {
        cout << format_answer(i + 1, assess_board(boards[i])) << '\n';
    }
    return 0;
}
