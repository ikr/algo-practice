#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;
using Seg = pair<int, int>;
enum class Dir { RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3 };
enum class Cmd { MOVE, TURN_LEFT, TURN_RIGHT };

struct State final {
    Coord rc;
    Dir dir;
};

static const map<Dir, Coord> DS{{Dir::UP, {-1, 0}},
                                {Dir::RIGHT, {0, 1}},
                                {Dir::DOWN, {1, 0}},
                                {Dir::LEFT, {0, -1}}};

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

char one_ahead(const vector<string> &grid, const State &st) {
    return at(grid, st.rc + DS.at(st.dir));
}

vector<Cmd> atomic_commands(const vector<string> &command_tokens) {
    vector<Cmd> result;
    for (const auto &t : command_tokens) {
        if (t == "L") {
            result.push_back(Cmd::TURN_LEFT);
        } else if (t == "R") {
            result.push_back(Cmd::TURN_RIGHT);
        } else {
            const auto k = stoi(t);
            for (int i = 0; i != k; ++i) result.push_back(Cmd::MOVE);
        }
    }
    return result;
}

constexpr Dir ddir(const Dir dir, const int delta) {
    int x = (inof(dir) + delta) % 4;
    x += 4;
    x %= 4;
    return static_cast<Dir>(x);
}

constexpr bool is_within(const Seg ab, const int x) {
    return ab.first <= x && x < ab.second;
}

constexpr int face_number(const int edge, const Coord rc) {
    const auto [ro, co] = rc;

    if (is_within({0, edge}, ro) && is_within({edge, 2 * edge}, co)) {
        return 1;
    }

    if (is_within({0, edge}, ro) && is_within({2 * edge, 3 * edge}, co)) {
        return 2;
    }

    if (is_within({edge, 2 * edge}, ro) && is_within({edge, 2 * edge}, co)) {
        return 3;
    }

    if (is_within({2 * edge, 3 * edge}, ro) && is_within({0, edge}, co)) {
        return 4;
    }

    if (is_within({2 * edge, 3 * edge}, ro) &&
        is_within({edge, 2 * edge}, co)) {
        return 5;
    }

    if (is_within({3 * edge, 4 * edge}, ro) && is_within({0, edge}, co)) {
        return 6;
    }

    assert(false && "Impossible cube face");
    return 0;
}

State route(const vector<string> &grid, const vector<Cmd> &commands, State st) {
    const auto edge = sz(grid) / 4;

    const auto wrapped_state = [&]() -> State {
        const auto f = face_number(edge, st.rc);

        if (f == 1 && st.dir == Dir::LEFT) {
            return {{2 * edge + RO(st.rc), 0}, Dir::RIGHT};
        }

        if (f == 1 && st.dir == Dir::UP) {
            return {{3 * edge + CO(st.rc) - edge, 0}, Dir::RIGHT};
        }

        if (f == 2 && st.dir == Dir::UP) {
            return {{4 * edge - 1, CO(st.rc) - 2 * edge}, Dir::UP};
        }

        if (f == 2 && st.dir == Dir::RIGHT) {
            return {{2 * edge + RO(st.rc), 2 * edge - 1}, Dir::LEFT};
        }

        if (f == 2 && st.dir == Dir::DOWN) {
            return {{edge + CO(st.rc) - 2 * edge, 2 * edge - 1}, Dir::LEFT};
        }

        if (f == 3 && st.dir == Dir::LEFT) {
            return {{2 * edge, RO(st.rc) - edge}, Dir::DOWN};
        }

        if (f == 3 && st.dir == Dir::RIGHT) {
            return {{edge - 1, 2 * edge + RO(st.rc) - edge}, Dir::UP};
        }

        if (f == 4 && st.dir == Dir::LEFT) {
            return {{RO(st.rc) - 2 * edge, edge}, Dir::RIGHT};
        }

        if (f == 4 && st.dir == Dir::UP) {
            return {{edge + CO(st.rc), edge}, Dir::RIGHT};
        }

        if (f == 5 && st.dir == Dir::RIGHT) {
            return {{RO(st.rc) - 2 * edge, 3 * edge - 1}, Dir::LEFT};
        }

        if (f == 5 && st.dir == Dir::DOWN) {
            return {{3 * edge + CO(st.rc) - edge, edge - 1}, Dir::LEFT};
        }

        if (f == 6 && st.dir == Dir::LEFT) {
            return {{0, edge + RO(st.rc) - 3 * edge}, Dir::DOWN};
        }

        if (f == 6 && st.dir == Dir::RIGHT) {
            return {{3 * edge - 1, edge + RO(st.rc) - 3 * edge}, Dir::UP};
        }

        if (f == 6 && st.dir == Dir::DOWN) {
            return {{0, 2 * edge + CO(st.rc)}, Dir::DOWN};
        }

        assert(false && "Failed to wrap");
        return st;
    };

    for (const auto cmd : commands) {
        switch (cmd) {
        case Cmd::TURN_LEFT:
            st.dir = ddir(st.dir, -1);
            break;
        case Cmd::TURN_RIGHT:
            st.dir = ddir(st.dir, 1);
            break;
        case Cmd::MOVE:
            if (const auto a = one_ahead(grid, st); a == ' ') {
                const auto w_st = wrapped_state();
                const auto w = at(grid, w_st.rc);
                assert(w != ' ');
                if (w == '.') st = w_st;
            } else {
                if (a == '.') st.rc = st.rc + DS.at(st.dir);
            }
            break;
        }
    }

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

    cout << final_password(route(
                grid, atomic_commands(tokenize_command_source(command_source)),
                State{Coord{0, sz(grid) / 4}, Dir::RIGHT}))
         << '\n';
    return 0;
}
