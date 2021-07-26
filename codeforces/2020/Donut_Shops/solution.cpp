#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        ll a, b, c;
        cin >> a >> b >> c;

        if (c == a) {
            cout << "-1 2\n";
        } else if (c < a) {
            cout << "-1 1\n";
        } else if (b * a <= c) {
            cout << "1 -1\n";
        } else {
            cout << "1 " << b << '\n';
        }
    }

    return 0;
}
