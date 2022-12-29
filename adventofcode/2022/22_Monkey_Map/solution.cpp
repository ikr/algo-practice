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

vector<Seg> vert_spreads(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = max_width(grid);
    vector<Seg> result(W, {-1, -1});

    for (int co = 0; co < W; ++co) {
        auto &a = result[co].first;
        auto &b = result[co].second;

        for (int ro = 0; ro < H; ++ro) {
            if (at(grid, {ro, co}) == ' ') {
                if (a != -1 && b == -1) b = ro - 1;
            } else {
                if (a == -1) a = ro;
            }
        }

        if (b == -1) b = H - 1;
    }

    return result;
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

State route(const vector<string> &grid, const vector<Cmd> &commands, State st) {
    const auto horz = horz_spreads(grid);
    const auto vert = vert_spreads(grid);

    const auto wrapped_location = [&]() -> Coord {
        switch (st.dir) {
        case Dir::RIGHT:
            return {RO(st.rc), horz[RO(st.rc)].first};
        case Dir::DOWN:
            return {vert[CO(st.rc)].first, CO(st.rc)};
        case Dir::LEFT:
            return {RO(st.rc), horz[RO(st.rc)].second};
        case Dir::UP:
            return {vert[CO(st.rc)].first, CO(st.rc)};
        }

        assert(false && "/o\\");
        return st.rc;
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
                const auto w_rc = wrapped_location();
                const auto w = at(grid, w_rc);
                assert(w != ' ');
                if (w == '.') st.rc = w_rc;
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
                State{Coord{0, 0}, Dir::RIGHT}))
         << '\n';
    return 0;
}
