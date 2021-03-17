#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

enum class Answer { WHITE_IN_CHECK, BLACK_IN_CHECK, NONE_IN_CHECK };

using Row = array<char, 8>;
using Rows = array<Row, 8>;

ostream &operator<<(ostream &os, const Row &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

ostream &operator<<(ostream &os, const Rows &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

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

Answer assess_position(const Rows &board) { return Answer::NONE_IN_CHECK; }

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

    for (const auto &board : boards) {
        cout << board << '\n';
    }

    for (int i = 0; i < sz(boards); ++i) {
        if (i) cout << '\n';
        cout << format_answer(i + 1, assess_position(boards[i]));
    }
    return 0;
}
