#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int D = 9;
static constexpr int DD = 3;

vector<vector<int>> transpose(const vector<vector<int>> &grid) {
    vector<vector<int>> result(sz(grid[0]), vector(sz(grid), 0));

    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[0]); ++co) {
            result[co][ro] = grid[ro][co];
        }
    }

    return result;
}

bool is_proper_row(const vector<int> &xs) {
    set<int> seen(cbegin(xs), cend(xs));
    return sz(seen) == sz(xs);
}

vector<int> box_of(const vector<vector<int>> &grid, const int i, const int j) {
    vector<int> result;
    const auto r0 = i * DD;
    const auto c0 = j * DD;

    for (int dro = 0; dro < DD; ++dro) {
        for (int dco = 0; dco < DD; ++dco) {
            result.push_back(grid[r0 + dro][c0 + dco]);
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    vector<vector<int>> grid(D, vector(D, 0));
    for (auto &row : grid) {
        for (auto &x : row) cin >> x;
    }

    const auto grid_ = transpose(grid);

    vector<vector<int>> boxes;
    for (int i = 0; i < DD; ++i) {
        for (int j = 0; j < DD; ++j) boxes.emplace_back(box_of(grid, i, j));
    }

    const auto yes = ranges::all_of(grid, is_proper_row) &&
                     ranges::all_of(grid_, is_proper_row) &&
                     ranges::all_of(boxes, is_proper_row);
    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
