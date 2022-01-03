#include <bits/stdc++.h>
using namespace std;

using Rooms = array<array<char, 2>, 4>;
using Hallway = array<char, 11>;

struct State final {
    Rooms rs;
    Hallway hw;
};

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

int step_energy(const char x) {
    const array<int, 4> es{1, 10, 100, 1000};
    return es[inof(x) - inof('A')];
}

constexpr bool is_open_space(const char x) { return x == '.'; }

bool can_move_in_hallway(const Hallway &hw, const int lo, const int hi) {
    return all_of(cbegin(hw) + lo, cbegin(hw) + hi + 1, is_open_space);
}

vector<pair<State, int>> adjacent_for_room_0(const State &st) {
    vector<pair<State, int>> result;
    if (is_open_space(st.rs[0][0]) && is_open_space(st.rs[0][1])) return result;
    const auto x = is_open_space(st.rs[0][0]) ? st.rs[0][1] : st.rs[0][0];
    const auto takeoff = is_open_space(st.rs[0][0]) ? 2 : 1;

    // TODO

    return result;
}

vector<pair<State, int>> adjacent(const State &st) {
    vector<pair<State, int>> result;
    // TODO
    return result;
}

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
