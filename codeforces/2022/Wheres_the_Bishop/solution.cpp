#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<int, int> bcoord(const vector<string> &grid) {
    for (int ro = 1; ro <= 6; ++ro) {
        for (int co = 1; co <= 6; ++co) {
            if (grid[ro - 1][co - 1] == '#' && grid[ro - 1][co + 1] == '#' &&
                grid[ro + 1][co - 1] == '#' && grid[ro + 1][co + 1] == '#' &&
                grid[ro][co] == '#') {
                return {ro, co};
            }
        }
    }

    assert(false && "/o\\");
    return {-1, -1};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        vector<string> grid(8);
        for (auto &row : grid) {
            cin >> row;
        }

        const auto [ro, co] = bcoord(grid);
        cout << (ro + 1) << ' ' << (co + 1) << '\n';
    }

    return 0;
}
