#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    const bool yes = !(d < a || c > b);
    cout << (yes ? "Yes\n" : "No\n");

    return 0;
}
