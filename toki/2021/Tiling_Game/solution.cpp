#include <bits/stdc++.h>
using namespace std;

int min_tiles(const int n, const int m) {
    if (n == 1 && m == 1) return 2;
    if (n % 2 == 0 && m % 2 == 0) return n * m;

    if (n % 2 && m % 2) return n + m + min_tiles(n - 1, m - 1);
    if (n % 2) return m + 1 + min_tiles(n - 1, m);
    if (m % 2) return n + 1 + min_tiles(n, m - 1);

    assert(false && "Logical error");
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    cout << min_tiles(n, m) << '\n';

    return 0;
}
