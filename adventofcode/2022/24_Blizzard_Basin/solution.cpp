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

struct Blizzards final {
    int H;
    int W;
    array<set<Coord>, 4> xss;

    Blizzards() : H{}, W{} { xss.fill(set<Coord>()); }

    Blizzards tick() const {
        Blizzards result;
        result.H = H;
        result.W = W;

        for (int i = 0; i < sz(DELTAS); ++i) {
            for (const auto &x : xss[i]) {
                auto [ro, co] = x + DELTAS[i];
                if (i % 2) {
                    co = ((co % W) + W) % W;
                } else {
                    ro = ((ro % H) + H) % H;
                }
                result.xss[i].emplace(ro, co);
            }
        }
        return result;
    }

    bool operator==(const Blizzards &o) const {
        if (&o == this) return true;
        return H == o.H && W == o.W && xss == o.xss;
    }

    bool contains(const Coord coord) const {
        return any_of(cbegin(xss), cend(xss),
                      [coord](const auto &xs) { return xs.contains(coord); });
    }
};

vector<Blizzards> all_blizzard_configurations(const Blizzards &bs) {
    vector<Blizzards> result{bs};
    for (;;) {
        auto bs_ = result.back().tick();
        if (bs_ == result[0]) break;
        result.emplace_back(move(bs_));
    }
    return result;
}

pair<int, int> min_steps_and_phase(const vector<Blizzards> &bss,
                                   const Coord start, const Coord finish,
                                   const int ii0) {
    const auto in_bounds = [&](const Coord &coord) -> bool {
        const auto [ro, co] = coord;
        return 0 <= ro && ro < bss[0].H && 0 <= co && co < bss[0].W;
    };

    const auto statically_adjacent = [&](const Coord &coord) -> vector<Coord> {
        if (coord == start) return {start, {0, 0}};
        if (coord == finish) return {finish, {bss[0].H - 1, bss[0].W - 1}};
        vector<Coord> result{coord};

        for (const auto &d : DELTAS) {
            if (in_bounds(coord + d)) result.push_back(coord + d);
        }

        if (coord == Coord{0, 0}) {
            result.push_back(start);
        } else if (coord == Coord{bss[0].H - 1, bss[0].W - 1}) {
            result.push_back(finish);
        }
        return result;
    };

    const auto adjacent = [&](const IiCoord &iicoord) -> vector<IiCoord> {
        const auto [ii, ro, co] = iicoord;
        const auto jj = (ii + 1) % sz(bss);
        auto sa = statically_adjacent({ro, co});

        sa.erase(remove_if(begin(sa), end(sa),
                           [&](const Coord a) { return bss[jj].contains(a); }),
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
    const auto bss = all_blizzard_configurations(bs);
    const auto [A, ii] = min_steps_and_phase(bss, Coord{-1, 0},
                                             Coord{bss[0].H, bss[0].W - 1}, 0);
    cerr << "A:" << A << " ii:" << ii << endl;
    const auto [B, jj] = min_steps_and_phase(bss, Coord{bss[0].H, bss[0].W - 1},
                                             Coord{-1, 0}, ii);
    cerr << "B:" << B << " jj:" << jj << endl;
    const auto [C, kk] = min_steps_and_phase(bss, Coord{-1, 0},
                                             Coord{bss[0].H, bss[0].W - 1}, jj);
    cerr << "C:" << C << " kk:" << kk << endl;

    cout << (A + B + C) << '\n';
    return 0;
}
