#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int A, B;
    cin >> A >> B;

    for (int x = 0; x <= 9; ++x) {
        if (A + B != x) {
            cout << x << '\n';
            break;
        }
    }

    return 0;
}
