#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<string> grid(N);
    for (auto &row : grid) cin >> row;

    auto ans = grid;

    for (int co = 1; co < N; ++co) {
        ans[0][co] = grid[0][co - 1];
    }

    for (int ro = 1; ro < N; ++ro) {
        ans[ro][N - 1] = grid[ro - 1][N - 1];
    }

    for (int co = N - 2; co >= 0; --co) {
        ans[N - 1][co] = grid[N - 1][co + 1];
    }

    for (int ro = N - 2; ro >= 0; --ro) {
        ans[ro][0] = grid[ro + 1][0];
    }

    for (const auto &row : ans) {
        cout << row << '\n';
    }
    return 0;
}
