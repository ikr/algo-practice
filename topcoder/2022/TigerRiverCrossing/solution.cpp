#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

vector<int> optimal_column_additions(const vector<string> &grid, const int co,
                                     const int hi) {
    const auto H = sz(grid);
    vector<int> best(H, 0);
    iota(begin(best), end(best), 0);

    const auto compute_candidate = [&](const int start,
                                       const int step) -> vector<int> {
        vector<int> ans;
        for (int ro = start; ro < H; ro += step) {
            if (ro < 0) continue;
            if (grid[ro][co] == '=') {
                ans.push_back(ro);
            }
        }
        return ans;
    };

    for (int step = 1; step <= hi; ++step) {
        for (int start = -step; start <= -1; ++start) {
            const auto candidate = compute_candidate(start, step);
            if (sz(candidate) < sz(best)) {
                best = candidate;
            }
        }
    }

    return best;
}

struct TigerRiverCrossing final {
    vector<string> addRocks(vector<string> grid, const int hi) const {
        const auto H = sz(grid);
        const auto W = sz(grid[0]);

        vector<int> best(H, 0);
        int best_co = 0;
        iota(begin(best), end(best), 0);

        for (int co = 0; co < W; ++co) {
            const auto candidate = optimal_column_additions(grid, co, hi);
            if (sz(candidate) < sz(best)) {
                best = candidate;
                best_co = co;
            }
        }

        for (const auto ro : best) {
            grid[ro][best_co] = 'O';
        }

        return grid;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = TigerRiverCrossing{}.addRocks({"===============", "========O======", "===============", "========O======", "=O=============", "========O======", "===============", "========O======", "===============", "========O======"}, 2);
        const auto expected = vector<string>{"===============", "========O======", "===============", "========O======", "=O=============", "========O======", "===============", "========O======", "===============", "========O======"};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = TigerRiverCrossing{}.addRocks({"===============", "========O======", "===============", "========O======", "=O=============", "========O======", "===============", "========O======", "===============", "========O======"}, 1);
        const auto expected = vector<string>{"========O======", "========O======", "========O======", "========O======", "=O======O======", "========O======", "========O======", "========O======", "========O======", "========O======"};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
