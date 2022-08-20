#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int ones_count(const vector<string> &grid) {
    return transform_reduce(
        cbegin(grid), cend(grid), 0, plus<int>{},
        [](const string &row) { return count(cbegin(row), cend(row), '1'); });
}

int max_ops(const vector<string> &grid) {}

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
    }

    return 0;
}
