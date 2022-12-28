#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using Coord = pair<int, int>;
using Seg = pair<int, int>;
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

char at(const vector<string> &grid, const Coord &rc) {
    const auto H = sz(grid);
    if (RO(rc) < 0 || H <= RO(rc)) return ' ';

    const auto W = sz(grid[RO(rc)]);
    if (CO(rc) < 0 || W <= CO(rc)) return ' ';

    return grid[RO(rc)][CO(rc)];
}

int max_width(const vector<string> &grid) {
    return transform_reduce(
        cbegin(grid), cend(grid), 0,
        [](const int a, const int b) { return max(a, b); },
        [](const string &s) { return sz(s); });
}

vector<Seg> horz_spreads(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = max_width(grid);
    vector<Seg> result(H, {-1, -1});

    for (int ro = 0; ro < H; ++ro) {
        auto &a = result[ro].first;
        auto &b = result[ro].second;

        for (int co = 0; co < W; ++co) {
            if (at(grid, {ro, co}) == ' ') {
                if (a != -1 && b == -1) b = co - 1;
            } else {
                if (a == -1) a = co;
            }
        }

        if (b == -1) b = W - 1;
    }

    return result;
}

State route(const vector<string> &grid, const vector<string> &commands,
            State st) {
    cerr << horz_spreads(grid) << endl;
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
