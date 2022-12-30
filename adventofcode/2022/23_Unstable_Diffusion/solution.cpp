#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;

static const array<array<Coord, 3>, 4> VARS{
    array{Coord{-1, 0}, Coord{-1, -1}, Coord{-1, 1}},
    array{Coord{1, 0}, Coord{1, -1}, Coord{1, 1}},
    array{Coord{0, -1}, Coord{-1, -1}, Coord{1, -1}},
    array{Coord{0, 1}, Coord{-1, 1}, Coord{1, 1}}};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

auto rotated_vars(const int phase) {
    assert(0 <= phase && phase < sz(VARS));
    auto result = VARS;
    rotate(begin(result), begin(result) + phase, end(result));
    return result;
}

set<Coord> evolve(const set<Coord> &src, const int phase) {
    const auto vars = rotated_vars(phase);
    map<Coord, Coord> proposals;
    map<Coord, int> hits;

    for (const auto &e : src) {
        const auto alone = [&]() -> bool {
            for (int dro = -1; dro <= 1; ++dro) {
                for (int dco = -1; dco <= 1; ++dco) {
                    if (!dro && !dco) continue;
                    if (src.contains(e + Coord{dro, dco})) return false;
                }
            }
            return true;
        }();
        if (alone) continue;

        for (const auto &deltas : vars) {
            if (none_of(cbegin(deltas), cend(deltas),
                        [&](const auto d) { return src.contains(e + d); })) {
                proposals[e] = e + deltas[0];
                ++hits[e + deltas[0]];
                break;
            }
        }
    }

    set<Coord> result;
    for (const auto &e : src) {
        if (proposals.contains(e) && hits.at(proposals.at(e)) == 1) {
            result.insert(proposals.at(e));
        } else {
            result.insert(e);
        }
    }
    return result;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        if (line != "") grid.push_back(line);
    }

    set<Coord> elves;
    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[ro]); ++co) {
            if (grid[ro][co] == '#') elves.emplace(ro, co);
        }
    }

    for (int i = 0; i < 10'000; ++i) {
        auto elves_ = evolve(elves, i % 4);
        if (elves == elves_) {
            cout << (i + 1) << '\n';
            break;
        }
        swap(elves, elves_);
    }
    return 0;
}
