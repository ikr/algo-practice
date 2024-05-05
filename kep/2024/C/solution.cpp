#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll g, l;
    cin >> g >> l;

    if (l % g) {
        cout << "-1\n";
    } else {
        cout << g << ' ' << l / g << '\n';
    }
    return 0;
}
