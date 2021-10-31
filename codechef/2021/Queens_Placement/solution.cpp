#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> suggest_board(const int n) {
    vector<string> ans(n, string(n, '.'));

    for (int i = 0; i < n - 3; ++i) {
        ans[i][i] = 'Q';
    }

    ans[n - 2][n - 2] = 'Q';

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        const auto grid = suggest_board(n);
        for (const auto &row : grid) {
            cout << row << '\n';
        }
    }

    return 0;
}
