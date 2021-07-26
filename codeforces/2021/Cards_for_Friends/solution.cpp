#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int count_halves(int x) {
    int ans = 0;

    while (x % 2 == 0) {
        x /= 2;
        ++ans;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int w, h, n;
        cin >> w >> h >> n;

        const int wh = count_halves(w);
        const int hh = count_halves(h);

        const ll a = min(wh, hh);
        const ll b = max(wh, hh);

        int sheets = (1LL << a) * (1LL << b);
        cout << (sheets >= n ? "YES\n" : "NO\n");
    }

    return 0;
}
