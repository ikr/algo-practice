#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int D = 10;

constexpr int circle_index(const int ro, const int co) {
    return min({ro, co, abs(ro - (D - 1)), abs(co - (D - 1))});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        vector<string> grid(D);
        for (auto &row : grid) {
            cin >> row;
        }

        int score{};
        for (int ro = 0; ro < D; ++ro) {
            for (int co = 0; co < D; ++co) {
                if (grid[ro][co] == 'X') {
                    score += circle_index(ro, co) + 1;
                }
            }
        }
        cout << score << '\n';
    }

    return 0;
}
