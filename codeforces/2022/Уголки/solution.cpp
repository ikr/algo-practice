#include <bits/stdc++.h>
using namespace std;

static const set<string> DOT{"1000", "0100", "0010", "0001"};
static const set<string> BRICK{"1100", "0011", "1010", "0101"};
static const set<string> CHECK{"1001", "0110"};
static const set<string> HOLE{"0111", "1011", "1101", "1110"};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int ones_count(const vector<string> &grid) {
    return transform_reduce(
        cbegin(grid), cend(grid), 0, plus<int>{},
        [](const string &row) { return count(cbegin(row), cend(row), '1'); });
}

int max_ops(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    const auto total = ones_count(grid);
    int result{};

    for (int ro = 0; ro < H - 1; ++ro) {
        for (int co = 0; co < W - 1; ++co) {
            const string box{grid[ro][co], grid[ro][co + 1], grid[ro + 1][co],
                             grid[ro + 1][co + 1]};
            if (box == "0000" || DOT.count(box) || BRICK.count(box) ||
                CHECK.count(box)) {
                return total;
            }

            if (box == "1111") {
                result = max(result, 1 + total - 3);
                continue;
            }

            if (HOLE.count(box)) {
                result = max(result, 1 + total - 2);
                continue;
            }

            assert(false && "/o\\");
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int H, W;
        cin >> H >> W;

        vector<string> grid(H);
        for (auto &row : grid) {
            cin >> row;
            assert(sz(row) == W);
        }

        cout << max_ops(grid) << '\n';
    }

    return 0;
}
