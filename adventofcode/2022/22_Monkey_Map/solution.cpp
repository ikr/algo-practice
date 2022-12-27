#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;
enum class Facing { RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3 };

struct State final {
    Coord rc;
    Facing f;
};

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

constexpr int RO(const Coord rc) { return rc.first; }
constexpr int CO(const Coord rc) { return rc.second; }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int final_password(const State &st) {
    const auto [rc, f] = st;
    return 1000 * (RO(rc) + 1) + 4 * (CO(rc) + 1) + inof(f);
}

vector<string> tokenize_command_source(const string &src) {
    const regex pattern("[0-9]+|L|R");
    vector<string> result;
    copy(sregex_token_iterator(cbegin(src), cend(src), pattern),
         sregex_token_iterator(), back_inserter(result));
    return result;
}

State route(const vector<string> &grid, const vector<string> &commands,
            State st) {
    return st;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        if (line == "") break;
        grid.push_back(line);
    }

    string command_source;
    cin >> command_source;

    cout << final_password(route(grid, tokenize_command_source(command_source),
                                 State{Coord{0, 0}, Facing::RIGHT}))
         << '\n';
    return 0;
}
