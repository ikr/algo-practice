#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;
using IiCoord = tuple<int, int, int>;

enum class Dir { U = 0, R = 1, D = 2, L = 3 };

static constexpr array<Coord, 4> DELTAS{Coord{-1, 0}, Coord{0, 1}, Coord{1, 0},
                                        Coord{0, -1}};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename T>
constexpr pair<T, T> scaled(const pair<T, T> a, const T k) {
    return {a.first * k, a.second * k};
}

struct Blizzards final {
    int H;
    int W;
    array<set<Coord>, 4> xss;

    Blizzards() : H{}, W{} { xss.fill(set<Coord>()); }

    bool cover(const int t, const Coord coord) const {
        for (int i = 0; i < 4; ++i) {
            auto [ro, co] = coord + scaled(DELTAS[i], -1 * t);
            if (i % 2) {
                co = ((co % W) + W) % W;
            } else {
                ro = ((ro % H) + H) % H;
            }

            if (xss[i].contains({ro, co})) return true;
        }
        return false;
    }
};

pair<int, int> min_steps_and_phase(const Blizzards &bs, const Coord start,
                                   const Coord finish, const int ii0) {
    const auto in_bounds = [&](const Coord &coord) -> bool {
        const auto [ro, co] = coord;
        return 0 <= ro && ro < bs.H && 0 <= co && co < bs.W;
    };

    const auto statically_adjacent = [&](const Coord &coord) -> vector<Coord> {
        if (coord == Coord{-1, 0}) return {{-1, 0}, {0, 0}};
        if (coord == Coord{bs.H, bs.W - 1}) {
            return {{bs.H, bs.W - 1}, {bs.H - 1, bs.W - 1}};
        }

        vector<Coord> result{coord};

        for (const auto &d : DELTAS) {
            if (in_bounds(coord + d)) result.push_back(coord + d);
        }

        if (coord == Coord{0, 0}) {
            result.push_back(Coord{-1, 0});
        } else if (coord == Coord{bs.H - 1, bs.W - 1}) {
            result.push_back(Coord{bs.H, bs.W - 1});
        }
        return result;
    };

    const auto adjacent = [&](const IiCoord &iicoord) -> vector<IiCoord> {
        const auto m = lcm(bs.H, bs.W);
        const auto [ii, ro, co] = iicoord;
        const auto jj = (ii + 1) % m;
        auto sa = statically_adjacent({ro, co});

        sa.erase(remove_if(begin(sa), end(sa),
                           [&](const Coord a) { return bs.cover(jj, a); }),
                 end(sa));

        vector<IiCoord> result(sz(sa));
        transform(cbegin(sa), cend(sa), begin(result), [jj](const Coord a) {
            return IiCoord{jj, a.first, a.second};
        });
        return result;
    };

    map<IiCoord, int> D;
    D[{ii0, start.first, start.second}] = 0;

    queue<IiCoord> q;
    q.emplace(ii0, start.first, start.second);

    while (!q.empty()) {
        const auto iicoord = q.front();
        q.pop();

        for (const auto &a : adjacent(iicoord)) {
            if (D.contains(a)) continue;
            D[a] = D.at(iicoord) + 1;

            const auto [jj, ro, co] = a;
            if (Coord{ro, co} == finish) return {D.at(a), jj};
            q.push(a);
        }
    }

    return {INT_MAX, 0};
}

int main() {
    Blizzards bs{};

    for (string line; getline(cin, line);) {
        if (line.substr(0, 3) == "#.#" || line.substr(0, 3) == "###") continue;
        line = line.substr(1, sz(line) - 2);

        for (int co = 0; co < sz(line); ++co) {
            switch (line[co]) {
            case '^':
                bs.xss[inof(Dir::U)].emplace(bs.H, co);
                break;
            case '>':
                bs.xss[inof(Dir::R)].emplace(bs.H, co);
                break;
            case 'v':
                bs.xss[inof(Dir::D)].emplace(bs.H, co);
                break;
            case '<':
                bs.xss[inof(Dir::L)].emplace(bs.H, co);
                break;
            }
        }

        ++bs.H;
        bs.W = sz(line);
    }

    const auto [A, ii] =
        min_steps_and_phase(bs, Coord{-1, 0}, Coord{bs.H, bs.W - 1}, 0);
    cerr << "A:" << A << " ii:" << ii << endl;
    const auto [B, jj] =
        min_steps_and_phase(bs, Coord{bs.H, bs.W - 1}, Coord{-1, 0}, ii);
    cerr << "B:" << B << " jj:" << jj << endl;
    const auto [C, kk] =
        min_steps_and_phase(bs, Coord{-1, 0}, Coord{bs.H, bs.W - 1}, jj);
    cerr << "C:" << C << " kk:" << kk << endl;

    cout << (A + B + C) << '\n';
    return 0;
}
