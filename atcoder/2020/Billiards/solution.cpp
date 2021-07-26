#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(9) << fixed;

    double sx, sy, gx, gy;
    cin >> sx >> sy >> gx >> gy;

    if (sx == gx) {
        cout << sx << '\n';
    } else {
        const double a = (gy + sy) / (gx - sx);
        const double b = gy - a * gx;
        cout << (-b / a) << '\n';
    }

    return 0;
}
