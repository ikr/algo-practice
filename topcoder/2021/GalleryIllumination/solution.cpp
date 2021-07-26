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

void illuminate(vector<string> &grid, const int ro, const int co) {
    const int H = sz(grid);
    const int W = sz(grid[0]);

    for (int i = ro - 1; i >= 0; --i) {
        char &x = grid[i][co];

        if (x == '#') break;
        if (x == 'O') continue;
        assert(x == '.' || x == '*');
        x = '*';
    }

    for (int j = co + 1; j < W; ++j) {
        char &x = grid[ro][j];

        if (x == '#') break;
        if (x == 'O') continue;
        assert(x == '.' || x == '*');
        x = '*';
    }

    for (int i = ro + 1; i < H; ++i) {
        char &x = grid[i][co];

        if (x == '#') break;
        if (x == 'O') continue;
        assert(x == '.' || x == '*');
        x = '*';
    }

    for (int j = co - 1; j >= 0; --j) {
        char &x = grid[ro][j];

        if (x == '#') break;
        if (x == 'O') continue;
        assert(x == '.' || x == '*');
        x = '*';
    }
}

struct GalleryIllumination final {
    int countDarkCells(const int H, const int W, vector<string> grid) const {
        for (int ro = 0; ro < H; ++ro) {
            for (int co = 0; co < W; ++co) {
                if (grid[ro][co] == 'O') illuminate(grid, ro, co);
            }
        }

        int ans = 0;

        for (const auto &row : grid) {
            for (const auto x : row) {
                if (x == '.') ++ans;
            }
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = GalleryIllumination{}.countDarkCells(3, 4, {"....", "....", "...."});
        const auto expected = 12;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = GalleryIllumination{}.countDarkCells(4, 5, {".....", ".O...", ".....", "....."});
        const auto expected = 12;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
