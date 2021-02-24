#include <bits/stdc++.h>
using namespace std;

int category(const int m, const int h) {
    if (m <= 18 * h * h) return 1;
    if (m >= 30 * h * h) return 4;
    if (m >= 19 * h * h && m <= 24 * h * h) return 2;
    if (m >= 25 * h * h && m <= 29 * h * h) return 3;
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int m, h;
        cin >> m >> h;

        cout << category(m, h) << '\n';
    }

    return 0;
}
