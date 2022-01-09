#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int p, q;
    cin >> p >> q;

    const int total = p * p + q * q + 1;

    if (total % 4) {
        cout << -1 << '\n';
    } else {
        cout << (total / 4) << '\n';
    }

    return 0;
}
