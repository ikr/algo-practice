#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> vector<T> concat(vector<T> xs, const vector<T> &ys) {
    xs.insert(cend(xs), cbegin(ys), cend(ys));
    return xs;
}

enum class Dir { N, NE, E, SE, S, SW, W, NW, Z };

static const vector<Dir> PLUS_DIRS{Dir::N, Dir::E, Dir::S, Dir::W};
static const vector<Dir> X_DIRS{Dir::NE, Dir::SE, Dir::SW, Dir::NW};
static const vector<Dir> ALL_DIRS = concat(PLUS_DIRS, X_DIRS);

using Coord = complex<int>;
constexpr int row(const Coord coord) { return coord.real(); }
constexpr int col(const Coord coord) { return coord.imag(); }

static constexpr int SZ = 8;

constexpr bool in_bounds(const Coord p) {
    return 1 <= row(p) && row(p) <= SZ && 1 <= col(p) && col(p) <= SZ;
}

int leeway(const Coord p0, const Coord st) {
    int result{};
    while (in_bounds(p0 + (result + 1) * st)) ++result;
    return result;
}

constexpr Coord step_in(const Dir d) {
    switch (d) {
    case Dir::N:
        return {-1, 0};
    case Dir::NE:
        return {-1, 1};
    case Dir::E:
        return {0, 1};
    case Dir::SE:
        return {1, 1};
    case Dir::S:
        return {1, 0};
    case Dir::SW:
        return {1, -1};
    case Dir::W:
        return {0, -1};
    case Dir::NW:
        return {-1, -1};
    default:
        assert(false && "Unexpected Dir");
        return {0, 0};
    }
}

template <typename T>
vector<vector<T>> cartesian_product(const vector<vector<T>> &src) {
    vector<vector<T>> result;
    if (src.empty() || any_of(cbegin(src), cend(src),
                              [](const auto &xs) { return xs.empty(); })) {
        return result;
    }

    result.push_back(vector<T>{});
    for (const auto &xs : src) {
        vector<vector<T>> next_gen;

        for (const auto x : xs) {
            for (auto curr : result) {
                curr.push_back(x);
                next_gen.push_back(curr);
            }
        }

        result = next_gen;
    }

    return result;
}

vector<Dir> piece_dirs(const string &name) {
    if (name == "rook") return concat(PLUS_DIRS, vector{Dir::Z});
    if (name == "queen") return concat(ALL_DIRS, vector{Dir::Z});
    assert(name == "bishop");
    return concat(X_DIRS, vector{Dir::Z});
}

vector<int> one_to(const int x) {
    vector<int> result(x);
    iota(begin(result), end(result), 1);
    return result;
}

using Tri = tuple<int, int, int>;

vector<Tri> trajectory(const Coord p0, const Dir dir, const int steps,
                       const int standing_time) {
    vector<Tri> result;

    if (dir == Dir::Z) {
        for (int i = 1; i <= steps + standing_time; ++i) {
            result.emplace_back(i, row(p0), col(p0));
        }

        return result;
    }

    for (int i = 1; i <= steps; ++i) {
        const auto p = p0 + step_in(dir) * i;
        result.emplace_back(i, row(p), col(p));
    }

    for (int i = steps + 1; i <= steps + standing_time; ++i) {
        const auto p = p0 + step_in(dir) * steps;
        result.emplace_back(i, row(p), col(p));
    }

    return result;
}

vector<Coord> as_coords(const vector<vector<int>> &positions) {
    vector<Coord> result(sz(positions));
    transform(cbegin(positions), cend(positions), begin(result),
              [](const auto &x) {
                  return Coord{x[0], x[1]};
              });
    return result;
}

vector<vector<Dir>> dir_combos(const vector<string> &pieces) {
    vector<vector<Dir>> dirs_by_piece(sz(pieces));
    transform(cbegin(pieces), cend(pieces), begin(dirs_by_piece), piece_dirs);
    return cartesian_product(dirs_by_piece);
}

using Occ = array<array<array<bool, SZ + 1>, SZ + 1>, SZ + 1>;

bool occupy_if_possible(Occ &occ, const vector<Tri> &tr) {
    for (const auto tp : tr) {
        const auto [t, r, c] = tp;
        if (occ[t][r][c]) return false;
        occ[t][r][c] = true;
    }
    return true;
}

int count_games(const vector<Coord> &ps, const vector<Dir> &dirs) {
    vector<vector<int>> move_ranges(sz(ps));
    int hi{};
    for (int i = 0; i < sz(ps); ++i) {
        if (dirs[i] == Dir::Z) {
            move_ranges[i] = vector{0};
            continue;
        }

        const auto l = leeway(ps[i], step_in(dirs[i]));
        hi = max(hi, l);
        move_ranges[i] = one_to(l);
    }

    int ans{};
    const auto move_combos = cartesian_product(move_ranges);
    for (const auto &moves : move_combos) {
        assert(sz(moves) == sz(ps));
        Occ occ{};

        bool ok = true;
        for (int i = 0; i < sz(ps); ++i) {
            assert(moves[i] <= hi);
            const auto tr = trajectory(ps[i], dirs[i], moves[i], hi - moves[i]);

            if (!occupy_if_possible(occ, tr)) {
                ok = false;
                break;
            }
        }

        if (ok) ++ans;
    }

    return ans;
}

struct Solution final {
    int countCombinations(const vector<string> &pieces,
                          const vector<vector<int>> &positions) const {
        const auto ps = as_coords(positions);
        const auto cmb = dir_combos(pieces);

        return transform_reduce(
            cbegin(cmb), cend(cmb), 0, plus<int>{},
            [&ps](const auto &dirs) { return count_games(ps, dirs); });
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 1") {
        const auto actual = Solution{}.countCombinations({"rook"}, {{1, 1}});
        const auto expected = 15;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = Solution{}.countCombinations({"queen"}, {{1, 1}});
        const auto expected = 22;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = Solution{}.countCombinations({"bishop"}, {{4, 3}});
        const auto expected = 12;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = Solution{}.countCombinations({"rook", "rook"}, {{1, 1}, {8, 8}});
        const auto expected = 223;
        EXPECT(actual == expected);
    },
    CASE("Example 5") {
        const auto actual = Solution{}.countCombinations({"queen", "bishop"}, {{5, 7}, {3, 4}});
        const auto expected = 281;
        EXPECT(actual == expected);
    },
    CASE("Test case 272") {
        const auto actual = Solution{}.countCombinations(
            {"bishop","bishop","bishop","bishop"}, {{2,2},{4,4},{5,5},{8,8}});
        const auto expected = 3828;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
