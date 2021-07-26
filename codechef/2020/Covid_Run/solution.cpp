#include <bits/stdc++.h>
using namespace std;

bool will_reach(const int n, const int K, const int x, const int y) {
    const int k = K % n;
    const int d = gcd(n, k);
    return ((x - y + n) % n) % d == 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, k, x, y;
        cin >> n >> k >> x >> y;
        cout << (will_reach(n, k, x, y) ? "YES\n" : "NO\n");
    }

    return 0;
}
