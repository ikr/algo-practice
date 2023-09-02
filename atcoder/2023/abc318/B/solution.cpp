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

    vector<vector<bool>> grid(101, vector(101, false));

    for (int i = 0; i < N; ++i) {
        int A, B, C, D;
        cin >> A >> B >> C >> D;

        for (int ro = A; ro < B; ++ro) {
            for (int co = C; co < D; ++co) {
                grid[ro][co] = true;
            }
        }
    }

    int ans{};
    for (const auto &row : grid) {
        ans += inof(count(cbegin(row), cend(row), true));
    }
    cout << ans << '\n';
    return 0;
}
