#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static const string ALL_B{"BBBBBBBB"};
static const string ALL_R{"RRRRRRRR"};

string get_column(const vector<string> &grid, const int co) {
    string result;
    for (int ro = 0; ro < sz(grid); ++ro) {
        result += grid[ro][co];
    }
    return result;
}

char last_color(const vector<string> &grid) {
    for (const auto &row : grid) {
        if (row == ALL_R) {
            return 'R';
        }
    }

    for (int co = 0; co < sz(grid[0]); ++co) {
        const auto col = get_column(grid, co);
        if (col == ALL_B) {
            return 'B';
        }
    }

    assert(false && "/o\\");
    return '.';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        vector<string> grid(8);
        for (auto &row : grid) cin >> row;

        cout << last_color(grid) << '\n';
    }

    return 0;
}
