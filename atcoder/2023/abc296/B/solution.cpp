#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr char chof(const int x) { return static_cast<char>(x); }

pii star_roco(const vector<string> &grid) {
    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[ro]); ++co) {
            if (grid[ro][co] == '*') return {ro, co};
        }
    }

    assert(false && "/o\\");
    return {-1, -1};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    vector<string> grid(8, "");
    for (auto &row : grid) {
        cin >> row;
    }

    reverse(begin(grid), end(grid));
    const auto [ro, co] = star_roco(grid);

    string ans;
    ans += chof(inof('a') + co);
    ans += to_string(ro + 1);

    cout << ans << '\n';
    return 0;
}
