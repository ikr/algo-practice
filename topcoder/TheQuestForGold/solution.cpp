#include "lest.hpp"
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

using Coord = complex<int>;
constexpr int c_ro(const Coord coord) { return coord.real(); }
constexpr int c_co(const Coord coord) { return coord.imag(); }

bool in_bounds(const vector<string> &rows, const Coord coord) {
    const int h = sz(rows);
    const int w = sz(rows[0]);
    return c_ro(coord) >= 0 && c_ro(coord) < h && c_co(coord) >= 0 &&
           c_co(coord) < w;
}

bool is_at(const vector<string> &rows, const Coord coord, const char c) {
    return in_bounds(rows, coord) && rows[c_ro(coord)][c_co(coord)] == c;
}

bool signals_slime(const vector<string> &rows, const Coord coord) {
    for (const auto d : vector<Coord>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
        if (is_at(rows, coord + d, 'P')) return true;
    }

    return false;
}

Coord start_coord(const vector<string> &rows) {
    const int h = sz(rows);
    const int w = sz(rows[0]);

    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            if (rows[ro][co] == 'S') return {ro, co};
        }
    }

    assert(false && "no start");
    return {-1, -1};
}

struct TheQuestForGold final {
    string explore(const vector<string> &rows) const {
        const auto sc = start_coord(rows);
        if (signals_slime(rows, sc)) return "no gold";

        queue<Coord> q;
        q.push(sc);

        const int h = sz(rows);
        const int w = sz(rows[0]);
        vector<vector<bool>> discovered(h, vector<bool>(w, false));
        discovered[c_ro(sc)][c_co(sc)] = true;

        while (!q.empty()) {
            const auto u = q.front();
            q.pop();

            for (const auto d :
                 vector<Coord>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
                const auto v = u + d;

                if (!in_bounds(rows, v)) continue;
                if (discovered[c_ro(v)][c_co(v)]) continue;

                if (is_at(rows, v, 'T')) return "gold";
                if (signals_slime(rows, v) || is_at(rows, v, 'P')) continue;

                discovered[c_ro(v)][c_co(v)] = true;
                q.push(v);
            }
        }

        return "no gold";
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = TheQuestForGold{}.explore({"S....", ".....", "...T.", "....."});
        const auto expected = "gold";
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = TheQuestForGold{}.explore({"S....", "..P.P", ".P.T.", "....."});
        const auto expected = "no gold";
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = TheQuestForGold{}.explore({"S....", "P....", "...T.", "....."});
        const auto expected = "no gold";
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = TheQuestForGold{}.explore({"S....", ".....", "PPP..", ".....", ".....", ".....", "..PPP", "..T.."});
        const auto expected = "gold";
        EXPECT(actual == expected);
    },
    CASE("Example 5") {
        const auto actual = TheQuestForGold{}.explore({".......", ".......", "..P.P..", "..PPP..", "..P.P..", ".......", "..S...."});
        const auto expected = "no gold";
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
