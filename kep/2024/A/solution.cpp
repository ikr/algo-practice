#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;
    for (const auto &x : xs) {
        cout << x << x;
    }
    cout << '\n';
    return 0;
}
