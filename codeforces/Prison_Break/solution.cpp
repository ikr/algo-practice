#include <bits/stdc++.h>
using namespace std;

int escape_seconds(const int n, const int m, const int r, const int c) {
    return max({r - 1 + c - 1, r - 1 + m - c, n - r + m - c, n - r + c - 1});
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m, r, c;
        cin >> n >> m >> r >> c;
        cout << escape_seconds(n, m, r, c) << '\n';
    }

    return 0;
}
