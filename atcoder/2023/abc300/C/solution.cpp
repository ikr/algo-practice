#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

set<pii> centers(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    set<pii> ans;
    for (int ro = 1; ro < H - 1; ++ro) {
        for (int co = 1; co < W - 1; ++co) {
            if (grid[ro][co] != '#') continue;

            const vector<pii> straight{
                {ro - 1, co}, {ro, co + 1}, {ro + 1, co}, {ro, co - 1}};

            const vector<pii> diagonal{{ro - 1, co - 1},
                                       {ro - 1, co + 1},
                                       {ro + 1, co + 1},
                                       {ro + 1, co - 1}};

            if (all_of(cbegin(straight), cend(straight),
                       [&](const pii roco) {
                           const auto [r, c] = roco;
                           return grid[r][c] == '.';
                       }) &&
                all_of(cbegin(diagonal), cend(diagonal), [&](const pii roco) {
                    const auto [r, c] = roco;
                    return grid[r][c] == '#';
                })) {
                ans.emplace(ro, co);
            }
        }
    }
    return ans;
}

int cross_size(const vector<string> &grid, const pii center) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    int ans{};
    auto [ro, co] = center;

    while (ro + 1 < H && co + 1 < W && grid[ro + 1][co + 1] == '#') {
        ++ans;
        ++ro;
        ++co;
    }

    return ans;
}

vector<int> crosses_by_size(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    vector<int> ans(min(H, W), 0);

    for (const auto &center : centers(grid)) {
        const auto s = cross_size(grid, center);
        ++ans[s - 1];
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    vector<string> grid(H);
    for (auto &row : grid) {
        cin >> row;
        assert(sz(row) == W);
    }

    cout << crosses_by_size(grid) << '\n';
    return 0;
}
