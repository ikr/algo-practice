#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll solve(const ll n) {
    if (n == 1) return 0;
    if (n % 3) return -1;

    if (n % 6 == 0) {
        const auto sub = solve(n / 6);
        return sub == -1 ? -1 : 1 + sub;
    } else {
        const auto sub = solve(n * 2);
        return sub == -1 ? -1 : 1 + sub;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        cout << solve(n) << '\n';
    }

    return 0;
}
