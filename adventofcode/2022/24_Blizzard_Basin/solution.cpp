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

int min_steps(const Blizzards &bs) {
    const Coord start{-1, 0};
    const Coord finish{bs.H, bs.W - 1};
    const auto bss = all_blizzard_configurations(bs);

    const auto in_bounds = [&](const Coord &coord) -> bool {
        const auto [ro, co] = coord;
        return 0 <= ro && ro < bs.H && 0 <= co && co < bs.W;
    };

    const auto statically_adjacent = [&](const Coord &coord) -> vector<Coord> {
        if (coord == start) return {start, {0, 0}};
        vector<Coord> result{coord};

        for (const auto &d : DELTAS) {
            if (in_bounds(coord + d)) result.push_back(coord + d);
        }

        if (coord == Coord{0, 0}) {
            result.push_back(start);
        } else if (coord == Coord{bs.H - 1, bs.W - 1}) {
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
    D[{0, start.first, start.second}] = 0;

    queue<IiCoord> q;
    q.emplace(0, start.first, start.second);

    while (!q.empty()) {
        const auto iicoord = q.front();
        q.pop();

        for (const auto &a : adjacent(iicoord)) {
            if (D.contains(a)) continue;
            D[a] = D.at(iicoord) + 1;

            const auto [_, ro, co] = a;
            if (Coord{ro, co} == finish) return D.at(a);
            q.push(a);
        }
    }

    return INT_MAX;
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

    cout << min_steps(bs) << '\n';
    return 0;
}
