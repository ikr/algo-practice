#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using ll = long long;

int count_trees_along_direction(const vector<string> &rows, const pi dir) {
    const int H = rows.size();
    const int W = rows[0].size();
    const auto [dr, dc] = dir;

    int ans = 0;

    for (int r = 0, c = 0; r < H; r += dr, c += dc) {
        if (rows[r][c % W] == '#') ++ans;
    }

    return ans;
}

vector<pi> the_5_directions() {
    return {{1, 1}, {1, 3}, {1, 5}, {1, 7}, {2, 1}};
}

ll product_of_trees_count_in_5_directions(const vector<string> &rows) {
    ll ans = 1;

    for (const auto dir : the_5_directions()) {
        ans *= count_trees_along_direction(rows, dir);
    }

    return ans;
}

int main() {
    vector<string> rows;
    for (string row; getline(cin, row);) {
        rows.push_back(row);
    }

    cout << product_of_trees_count_in_5_directions(rows) << '\n';
    return 0;
}
