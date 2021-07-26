#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int d, t, s;
    cin >> d >> t >> s;
    bool ok = d <= s * t;

    cout << (ok ? "Yes" : "No") << '\n';

    return 0;
}
