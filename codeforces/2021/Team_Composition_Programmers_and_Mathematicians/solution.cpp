#include <bits/stdc++.h>
using namespace std;

int max_teams(const int a0, const int b0) {
    const auto recur = [](const int a, const int b) -> int {
        if (a + b < 4 || a <= 0 || b <= 0) return 0;

        const int x = min(a / 2, b / 2);
        const int y = min(a / 3, b);
        const int z = min(a, b / 3);

        return max({x ? (x + max_teams(a - 2 * x, b - 2 * x)) : 0,
                    y ? (y + max_teams(a - 3 * y, b - y)) : 0,
                    z ? (z + max_teams(a - z, b - 3 * z)) : 0});
    };

    int ans{};

    if (a0 >= 2 && b0 >= 2) {
        ans = max(ans, 1 + recur(a0 - 2, b0 - 2));
    }

    if (a0 >= 3 && b0 >= 1) {
        ans = max(ans, 1 + recur(a0 - 3, b0 - 1));
    }

    if (a0 >= 1 && b0 >= 3) {
        ans = max(ans, 1 + recur(a0 - 1, b0 - 3));
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;

        cout << max_teams(a, b) << '\n';
    }

    return 0;
}
