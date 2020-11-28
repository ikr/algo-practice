#include <bits/stdc++.h>
using namespace std;

int count_divisors(const int x) {
    int ans = (x == 1) ? 1 : 2;
    const int lim = sqrt(x);

    for (int i = 2; i <= lim; ++i) {
        if (x % i) continue;
        ++ans;
        if (x / i > lim) ++ans;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;
        cout << count_divisors(x) << '\n';
    }

    return 0;
}
