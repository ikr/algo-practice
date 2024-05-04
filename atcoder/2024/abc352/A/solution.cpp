#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, x, y, z;
    cin >> n >> x >> y >> z;
    if (x > y) swap(x, y);

    const auto yes = x < z && z < y;
    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
