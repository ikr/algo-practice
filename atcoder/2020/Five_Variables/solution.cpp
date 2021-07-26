#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 5;
    while (t--) {
        int x;
        cin >> x;
        if (!x) {
            cout << (5 - t) << '\n';
            break;
        }
    }

    return 0;
}
