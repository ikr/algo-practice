#include <bits/stdc++.h>
using namespace std;

vector<bool> sieve(const int n) {
    vector<bool> ans(n + 1, true);
    ans[0] = false;
    if (n) ans[1] = false;

    const int sq = sqrt(n);
    for (int i = 2; i <= sq; ++i) {
        if (!ans[i]) continue;
        for (int j = i * i; j <= n; j += i) ans[j] = false;
    }

    return ans;
}

int sum_up(const int n) {
    const auto prime = sieve(n);

    int s = 0;
    for (int i = 0; i <= n; ++i) {
        if (prime[i]) {
            s += i;
            s %= 10;
        }
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << sum_up(n) << '\n';
    }

    return 0;
}
