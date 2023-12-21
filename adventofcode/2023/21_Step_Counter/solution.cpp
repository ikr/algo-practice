#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Coord = pair<int, int>;
using TCoord = pair<int, int>;

static constexpr array Delta{Coord{-1, 0}, Coord{0, 1}, Coord{1, 0},
                             Coord{0, -1}};

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename T> size_t combine_hashes(const T &xs) {
    size_t seed = xs.size();
    for (const auto i : xs) seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}

template <typename T> void limit_size(vector<T> &xs) {
    if (sz(xs) > 4) xs.erase(cbegin(xs));
}

template <typename T> bool looped(const vector<T> &xs) {
    if (sz(xs) < 4) return false;
    return xs[0] == xs[2] && xs[1] == xs[3];
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        grid.push_back(line);
    }

    Coord src{-1, -1};
    for (int r = 0; r < sz(grid); ++r) {
        for (int c = 0; c < sz(grid[r]); ++c) {
            if (grid[r][c] == 'S') {
                src = {r, c};
                grid[r][c] = '.';
                break;
            }
        }
        if (src.first != -1) break;
    }
    assert(src.first != -1 && src.second != -1);

    const int M = sz(grid);
    assert(sz(grid) == sz(grid[0]));

    const auto inf_grid_at = [&](const Coord p) -> char {
        const auto r = ((p.first % M) + M) % M;
        const auto c = ((p.second % M) + M) % M;
        return grid[r][c];
    };

    const auto adjacent = [&](const Coord p) {
        vector<Coord> ans;
        for (const auto &d : Delta) {
            const auto np = p + d;
            if (inf_grid_at(np) == '#') continue;
            ans.push_back(np);
        }
        return ans;
    };

    const auto containing_tile = [&](const Coord p) -> TCoord {
        return {p.first / M, p.second / M};
    };

    const auto tile_left_top = [&](const TCoord tp) -> Coord {
        return {tp.first * M, tp.second * M};
    };

    set<Coord> gen{src};

    const auto tile_life = [&](const TCoord tp) -> vector<int> {
        const auto [r0, c0] = tile_left_top(tp);
        vector<int> result;

        for (int r = r0; r < r0 + M; ++r) {
            for (int c = c0; c < c0 + M; ++c) {
                if (gen.contains({r, c})) {
                    result.push_back((r - r0) * M + (c - c0));
                }
            }
        }

        return result;
    };

    const auto gather_tiles = [&]() -> set<TCoord> {
        set<TCoord> result;
        for (const auto &p : gen) result.insert(containing_tile(p));
        return result;
    };

    map<TCoord, vector<int>> last_life_sizes;
    map<TCoord, vector<size_t>> last_life_digests;
    set<TCoord> compressed;

    const auto observe_tile_return_can_compress = [&](const TCoord tp) -> bool {
        const auto life = tile_life(tp);

        last_life_sizes[tp].push_back(sz(life));
        limit_size(last_life_sizes[tp]);

        last_life_digests[tp].push_back(combine_hashes(life));
        limit_size(last_life_digests[tp]);

        return looped(last_life_digests.at(tp));
    };

    ll evn_stable{};
    ll odd_stable{};

    const auto compress = [&](const int step) -> void {
        auto tiles = gather_tiles();
        for (auto it = cbegin(tiles); it != cend(tiles);) {
            if (observe_tile_return_can_compress(*it)) {
                cerr << "Can compress tile " << *it << endl;
                const auto sizes = last_life_sizes.at(*it);
                if (step % 2 == 0) {
                    evn_stable += sizes.back();
                    odd_stable += sizes[sz(sizes) - 2];
                } else {
                    odd_stable += sizes.back();
                    evn_stable += sizes[sz(sizes) - 2];
                }

                last_life_sizes.erase(*it);
                last_life_digests.erase(*it);
                compressed.insert(*it);
                it = tiles.erase(it);
            } else {
                ++it;
            }
        }

        for (auto it = cbegin(gen); it != cend(gen);) {
            if (!tiles.contains(containing_tile(*it))) {
                it = gen.erase(it);
            } else {
                ++it;
            }
        }
    };

    const int MaxSteps = 100;
    for (int step = 1; step <= MaxSteps; ++step) {
        set<Coord> gen_;

        for (const auto &p : gen) {
            for (const auto &np : adjacent(p)) {
                if (compressed.contains(containing_tile(p))) continue;
                gen_.insert(np);
            }
        }

        swap(gen_, gen);
        compress(step);
        cerr << "gen size:" << sz(gen) << " evn_stable:" << evn_stable
             << " odd_stable:" << odd_stable << endl;
    }

    const auto result =
        ((MaxSteps % 2 == 0) ? evn_stable : odd_stable) + sz(gen);
    cout << result << '\n';
    return 0;
}
