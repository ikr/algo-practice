#include <bits/stdc++.h>
using namespace std;

int square(const int x) { return x * x; }

int max_tiles(const int n) {
    const int m = 2 * n;
    if (m < 4) return 0;
    if (m % 4 == 0) return square(m / 4) * 4;

    return square(m / 4) * 4 + 2 + ((m - 2) / 2 - 1) + ((m - 2) / 2 - 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    cout << max_tiles(n) << '\n';
    return 0;
}
