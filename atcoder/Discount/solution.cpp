#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(4) << fixed;

    double a, b;
    cin >> a >> b;
    const double x = b * 100.0 / a;
    cout << (100 - x) << '\n';

    return 0;
}
