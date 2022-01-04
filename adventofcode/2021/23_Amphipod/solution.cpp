#include <bits/stdc++.h>
using namespace std;

using Room = array<char, 4>;
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

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

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

bool only_spaces_before_xs(const Room &r, const char x) {
    const auto it = find(cbegin(r), cend(r), x);
    return all_of(cbegin(r), it, is_a(SPC)) && all_of(it, cend(r), is_a(x));
}

static const vector<int> DESTS{0, 1, 3, 5, 7, 9, 10};

vector<pair<State, int>> adjacent_by_room_k(const State &st, const int k) {
    const char tenant{chof(inof('A') + k)};

    vector<pair<State, int>> result;
    if (only_spaces_before_xs(st.rs[k], tenant)) return result;
    assert(is_partitioned(cbegin(st.rs[k]), cend(st.rs[k]), is_a(SPC)));

    const auto [a, takeoff, room] = [&]() -> tuple<char, int, Room> {
        const auto it =
            find_if_not(cbegin(st.rs[k]), cend(st.rs[k]), is_a(SPC));
        assert(it != cend(st.rs[k]));

        const auto i = inof(distance(cbegin(st.rs[k]), it));
        const auto x = *it;

        Room r = st.rs[k];
        r[i] = '.';
        return {x, i + 1, r};
    }();

    const auto rooms = [&](const Room &r) -> Rooms {
        Rooms rs = st.rs;
        rs[k] = r;
        return rs;
    }(room);

    const auto exit_i = 2 + k * 2;
    for (const auto i : DESTS) {
        if (can_move_in_hallway(st.hw, min(i, exit_i), max(i, exit_i))) {
            Hallway hw = st.hw;
            hw[i] = a;
            const auto steps = takeoff + abs(i - exit_i);
            result.emplace_back(State{rooms, hw}, steps * step_energy(a));
        }
    }

    return result;
}

vector<pair<State, int>> adjacent_by_hallway(const State &st) {
    vector<pair<State, int>> result;

    for (int i = 0; i < sz(st.hw); ++i) {
        if (st.hw[i] == SPC) continue;

        const auto a = st.hw[i];
        const auto k = inof(a) - inof('A');
        const auto entrance_i = 2 + k * 2;

        auto hw = st.hw;
        hw[i] = SPC;

        if (!can_move_in_hallway(hw, min(i, entrance_i), max(i, entrance_i)) ||
            !only_spaces_before_xs(st.rs[k], a)) {
            continue;
        }

        const auto [landing, room] = [&]() -> pair<int, Room> {
            const auto it = prev(find(cbegin(st.rs[k]), cend(st.rs[k]), a));
            const auto j = inof(distance(cbegin(st.rs[k]), it));

            Room r = st.rs[k];
            r[j] = a;
            return {j + 1, r};
        }();

        const auto rooms = [&](const Room &r) -> Rooms {
            Rooms rs = st.rs;
            rs[k] = r;
            return rs;
        }(room);

        const int steps = landing + abs(i - entrance_i);
        result.emplace_back(State{rooms, hw}, steps * step_energy(a));
    }

    return result;
}

vector<pair<State, int>> adjacent(const State &st) {
    auto result = adjacent_by_hallway(st);

    for (int k = 0; k < sz(st.rs); ++k) {
        const auto to_add = adjacent_by_room_k(st, k);
        result.insert(cend(result), cbegin(to_add), cend(to_add));
    }

    return result;
}

static constexpr Rooms RS_FINAL{
    Room{'A', 'A', 'A', 'A'}, Room{'B', 'B', 'B', 'B'},
    Room{'C', 'C', 'C', 'C'}, Room{'D', 'D', 'D', 'D'}};

int least_energy_to_organize(const Rooms &initial_rooms) {
    const State st0{initial_rooms, empty_hallway()};

    int result = INT_MAX;

    function<void(int, State)> recur;
    recur = [&](const int e, const State st) {
        if (st.rs == RS_FINAL) {
            assert(st.hw == empty_hallway());
            if (e < result) {
                cerr << "e:" << e << endl;
            }
            result = min(result, e);
        }

        for (const auto &[st_, e_] : adjacent(st)) {
            recur(e + e_, st_);
        }
    };

    recur(0, st0);
    return result;
}

static const array<string, 2> FOLDED{"  #D#C#B#A#", "  #D#B#A#C#"};

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        grid.push_back(line);
    }
    grid.insert(cbegin(grid) + 3, cbegin(FOLDED), cend(FOLDED));

    Rooms rooms{};
    for (int i = 0; i < sz(rooms); ++i) {
        for (int j = 0; j < sz(rooms[i]); ++j) {
            rooms[i][j] = grid[2 + j][3 + 2 * i];
        }
    }

    cout << least_energy_to_organize(rooms) << '\n';
    return 0;
}
