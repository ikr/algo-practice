#include <bits/stdc++.h>
using namespace std;

int find_max_radius(const int n) {
    for (int r = n; r >= 1; --r) {
        int points = 0;

        for (int x = 1; x < r; ++x) {
            const int rsq = r * r;

            for (int y = r - 1; y > r - x; --y) {
                if (x * x + y * y == rsq) ++points;
                if (points > 2) break;
            }

            if (points > 2) break;
        }

        if (points == 2) return r;
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    cout << find_max_radius(n) << '\n';

    return 0;
}
