#include <bits/stdc++.h>
using namespace std;

using Room = array<char, 2>;
using Rooms = array<Room, 4>;
using Hallway = array<char, 11>;

struct State final {
    Rooms rs;
    Hallway hw;
};

static constexpr char SPC = '.';

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

constexpr char chof(const int x) { return static_cast<char>(x); }

Hallway empty_hallway() {
    Hallway result;
    result.fill(SPC);
    return result;
}

int step_energy(const char x) {
    const array<int, 4> es{1, 10, 100, 1000};
    return es[inof(x) - inof('A')];
}

function<bool(char)> is_a(const char a) {
    return [a](const char x) { return x == a; };
}

bool can_move_in_hallway(const Hallway &hw, const int lo, const int hi) {
    return all_of(cbegin(hw) + lo, cbegin(hw) + hi + 1, is_a(SPC));
}

vector<pair<State, int>>
adjacent_for_room_k(const State &st, const int k,
                    const vector<int> &hallway_destinations) {
    const char tenant{chof(inof('A') + k)};

    vector<pair<State, int>> result;
    if (all_of(cbegin(st.rs[k]), cend(st.rs[k]), is_a(SPC))) return result;
    if (all_of(cbegin(st.rs[k]), cend(st.rs[k]), is_a(tenant))) return result;
    if (st.rs[k][0] == SPC && st.rs[k][1] == tenant) return result;

    const auto [a, takeoff, room] = [&]() -> tuple<char, int, Room> {
        if (st.rs[k][0] == SPC) {
            const auto x = st.rs[k][1];
            assert(x != SPC);
            assert(x != tenant);

            Room r = st.rs[k];
            r[1] = '.';
            return {x, 2, r};
        }

        Room r = st.rs[k];
        r[0] = '.';
        return {st.rs[k][0], 1, r};
    }();

    const auto rooms = [&](const Room &r) -> Rooms {
        Rooms rs = st.rs;
        rs[k] = r;
        return rs;
    }(room);

    const auto exit_i = 2 + k * 2;
    for (const auto i : hallway_destinations) {
        if (can_move_in_hallway(st.hw, min(i, exit_i), max(i, exit_i))) {
            Hallway hw = st.hw;
            hw[i] = a;
            const auto steps = takeoff + abs(i - exit_i);

            result.emplace_back(State{rooms, hw}, steps * step_energy(a));
        }
    }

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
