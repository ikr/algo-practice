#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ostream &operator<<(ostream &os, const vector<string> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

vector<string> transpose(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    vector<string> result(W, string(H, ' '));

    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[0]); ++co) {
            result[co][ro] = grid[ro][co];
        }
    }

    return result;
}

bool same_class(vector<string> grid_a, vector<string> grid_b) {
    grid_a = transpose(grid_a);
    sort(begin(grid_a), end(grid_a));

    grid_b = transpose(grid_b);
    sort(begin(grid_b), end(grid_b));

    return grid_a == grid_b;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    vector<string> grid_a(H);
    for (auto &row : grid_a) {
        cin >> row;
    }

    vector<string> grid_b(H);
    for (auto &row : grid_b) {
        cin >> row;
    }

    cout << (same_class(move(grid_a), move(grid_b)) ? "Yes" : "No") << '\n';
    return 0;
}
