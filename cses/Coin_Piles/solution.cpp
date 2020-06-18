#include <bits/stdc++.h>
using namespace std;

bool can_empty(const int a, const int b) {
    if (a < 0 || b < 0) return false;
    if (a == b) return a % 3 == 0;
    if (a > b) return can_empty(b, a);

    const int d = b - a;
    return can_empty(a - d, b - 2 * d);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << (can_empty(a, b) ? "YES" : "NO") << '\n';
    }

    return 0;
}
