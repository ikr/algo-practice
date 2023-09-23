#include <bits/stdc++.h>
using namespace std;

bool is_possible(const int S, const int D, const int K) {
    const array<int, 2> inventory{(S + D) * 2, S + 2 * D};
    const array<int, 2> need{K + 1, K};
    for (int i = 0; i < 2; ++i) {
        if (inventory[i] < need[i]) return false;
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int S, D, K;
        cin >> S >> D >> K;

        cout << "Case #" << i << ": " << (is_possible(S, D, K) ? "YES" : "NO")
             << '\n';
    }

    return 0;
}
