#include <bits/stdc++.h>
using namespace std;

int moves(const int a, const int b) {
    if (a == b) return 0;
    const int d = abs(a - b);
    const int r = d % 10;
    const int q = d / 10;

    return !!r ? q + 1 : q;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << moves(a, b) << '\n';
    }

    return 0;
}
