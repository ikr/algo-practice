#include "lest.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

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

struct ChamberCount final {
    int count(const vector<string> &grid) const {
        const int H = sz(grid);
        const int W = sz(grid[0]);

        vector<vector<int>> cs(H, vector<int>(W, 0));
        function<void(int, int, int)> dfs;
        dfs = [&](const int id, const int ro, const int co) {
            assert(grid[ro][co] == '.');
            assert(!cs[ro][co]);
            cs[ro][co] = id;

            if (ro > 0 && !cs[ro - 1][co] && grid[ro - 1][co] == '.') {
                dfs(id, ro - 1, co);
            }

            if (co < W - 1 && !cs[ro][co + 1] && grid[ro][co + 1] == '.') {
                dfs(id, ro, co + 1);
            }

            if (ro < H - 1 && !cs[ro + 1][co] && grid[ro + 1][co] == '.') {
                dfs(id, ro + 1, co);
            }

            if (co > 0 && !cs[ro][co - 1] && grid[ro][co - 1] == '.') {
                dfs(id, ro, co - 1);
            }
        };

        int id{};
        for (int ro = 0; ro < H; ++ro) {
            for (int co = 0; co < W; ++co) {
                if (grid[ro][co] == '.' && !cs[ro][co]) dfs(++id, ro, co);
            }
        }

        return id;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = ChamberCount{}.count({"...", "...", "..."});
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = ChamberCount{}.count({"XX", "XX"});
        const auto expected = 0;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
