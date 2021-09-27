#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string rotate_tile(const string &tile) {
    const auto a = tile[0];
    const auto b = tile[1];
    const auto c = tile[2];
    const auto d = tile[3];

    return string{c, a, d, b};
}

string tile_key(const string &tile) {
    const auto tile1 = rotate_tile(tile);
    const auto tile2 = rotate_tile(tile1);
    const auto tile3 = rotate_tile(tile2);
    assert(rotate_tile(tile3) == tile);

    return min({tile, tile1, tile2, tile3});
}

multiset<string> all_keys(const vector<string> &tiles) {
    multiset<string> ans;
    for (const auto &t : tiles) {
        ans.insert(tile_key(t));
    }
    return ans;
}

bool is_possible(const vector<string> &tiles, const vector<string> &grid) {
    auto ks = all_keys(tiles);

    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    for (int ro = 0; ro < H; ro += 2) {
        for (int co = 0; co < W; co += 2) {
            const auto a = grid[ro][co];
            const auto b = grid[ro][co + 1];
            const auto c = grid[ro + 1][co];
            const auto d = grid[ro + 1][co + 1];

            const auto k = tile_key(string{a, b, c, d});
            const auto it = ks.find(k);
            if (it == cend(ks)) return false;
            ks.erase(it);
        }
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int k;
    cin >> k;

    vector<string> tiles;
    tiles.reserve(k);

    while (k--) {
        string l1, l2;
        cin >> l1 >> l2;
        tiles.push_back(l1 + l2);
    }

    int H, W;
    cin >> H >> W;
    vector<string> grid(H, string(W, ' '));

    for (auto &row : grid) {
        cin >> row;
    }

    cout << (is_possible(tiles, grid) ? "Yes" : "No") << '\n';
    return 0;
}
