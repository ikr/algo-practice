#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int a, b;
    cin >> a >> b;

    const int hi = 2 * a + 100;
    cout << (hi - b) << '\n';

    return 0;
}
