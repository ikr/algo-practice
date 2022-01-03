#include <bits/stdc++.h>
using namespace std;

using Rooms = array<array<char, 2>, 4>;
using Hallway = array<char, 11>;

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T, size_t N, size_t M>
ostream &operator<<(ostream &os, const array<array<T, N>, M> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    vector<string> grid;

    for (string line; getline(cin, line);) {
        grid.push_back(line);
    }

    Rooms rooms{};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            rooms[i][j] = grid[2 + j][3 + 2 * i];
        }
    }

    cerr << rooms << endl;
    return 0;
}
