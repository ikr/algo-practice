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

template <typename T>
constexpr typename vector<T>::const_iterator cbegin(const vector<T> &xs) {
    return xs.cbegin();
}

template <typename T>
constexpr typename vector<T>::const_iterator cend(const vector<T> &xs) {
    return xs.cend();
}

string::const_iterator cbegin(const string &xs) { return xs.cbegin(); }
string::const_iterator cend(const string &xs) { return xs.cend(); }

static const vector<pii> DIRS{{-1, 0}, {-1, 1}, {0, 1},  {1, 1},
                              {1, 0},  {1, -1}, {0, -1}, {-1, -1}};

static const vector<string> FULL{"DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGD",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGG",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGD",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGG",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGD",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGG",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGD",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGG",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGD",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGG",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGD",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGG",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGD",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGG",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGD",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGG",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGD",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGG",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGD",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGG",
                                 "DOGODOGODOGODOGODOGODOGODOGODOGODOGODOGO"};

int count_dogs(const vector<string> &grid) {
    const int H = sz(grid);
    assert(H > 0);
    const int W = sz(grid[0]);
    assert(W > 0);

    const auto in_bounds = [&](const int ro, const int co) {
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    const auto read_in = [&](const int ro, const int co,
                             const pii dir) -> string {
        const auto dro = dir.first;
        const auto dco = dir.second;
        string ans;

        for (int i = 0; i < 3; ++i) {
            const int ro_ = ro + dro * i;
            const int co_ = co + dco * i;

            if (!in_bounds(ro_, co_)) break;
            ans += grid[ro_][co_];
        }

        return ans;
    };

    int ans{};

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] != 'D') continue;

            for (const auto dir : DIRS) {
                const auto buf = read_in(ro, co, dir);
                if (buf == string{"DOG"}) ++ans;
            }
        }
    }

    return ans;
}

struct DogsInAGrid final {
    vector<string> construct(const int N) const {
        vector<string> grid = FULL;

        const int H = sz(grid);
        assert(H > 0);
        const int W = sz(grid[0]);
        assert(W > 0);

        const auto in_bounds = [&](const int ro, const int co) {
            return 0 <= ro && ro < H && 0 <= co && co < W;
        };

        const auto read_in = [&](const int ro, const int co,
                                 const pii dir) -> string {
            const auto dro = dir.first;
            const auto dco = dir.second;
            string ans;

            for (int i = 0; i < 3; ++i) {
                const int ro_ = ro + dro * i;
                const int co_ = co + dco * i;

                if (!in_bounds(ro_, co_)) break;
                ans += grid[ro_][co_];
            }

            return ans;
        };

        const auto count_here = [&](const int ro, const int co) {
            if (grid[ro][co] != 'D') return 0;
            int ans = 0;

            for (const auto dir : DIRS) {
                const auto buf = read_in(ro, co, dir);
                if (buf == string{"DOG"}) ++ans;
            }

            return ans;
        };

        int curr = count_dogs(grid);

        for (int co = 0; co < W; ++co) {
            for (int ro = 0; ro < H; ++ro) {
                const auto c = count_here(ro, co);
                if (!c) continue;

                if (curr - c >= N) {
                    grid[ro][co] = 'O';
                    curr -= c;
                }

                if (curr == N) return grid;
            }
        }

        return grid;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto grid = DogsInAGrid{}.construct(4);
        const auto num = count_dogs(grid);
        EXPECT(num == 4);
    },
    CASE("Example 1") {
        const auto grid = DogsInAGrid{}.construct(2);
        const auto num = count_dogs(grid);
        EXPECT(num == 2);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
