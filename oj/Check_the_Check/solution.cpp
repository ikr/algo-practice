#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

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

    return 0;
}
