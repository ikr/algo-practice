#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << setprecision(7) << fixed;
    int x, y;
    cin >> x >> y;

    if (y == 1) {
        if (x == 0) {
            cout << "ALL GOOD\n";
        } else {
            cout << "IMPOSSIBLE\n";
        }
    } else {
        const auto result = 1.0 * x / (1.0 - y);
        cout << result << '\n';
    }
    return 0;
}
