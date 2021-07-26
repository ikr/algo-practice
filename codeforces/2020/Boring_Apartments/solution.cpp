#include <bits/stdc++.h>
using namespace std;

int count_digits(int x) {
    int ans = 0;
    while (x) {
        x /= 10;
        ++ans;
    }
    return ans;
}

int dialed(const int n) {
    int ans = 0;
    for (int i = 1; i <= 9; ++i) {
        int d = 0;
        while (d <= 10000) {
            if (d) ans += count_digits(d);
            if (d == n) return ans;
            d *= 10;
            d += i;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << dialed(n) << '\n';
    }

    return 0;
}
