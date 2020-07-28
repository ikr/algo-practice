#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int zeros(const int n) {
    int ans = 0;
    for (ll i = 5; i <= n; i *= 5) ans += n / i;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    cout << zeros(n) << '\n';

    return 0;
}
