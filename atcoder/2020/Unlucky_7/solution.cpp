#include <bits/stdc++.h>
using namespace std;

set<int> digits(int n, const int base) {
    set<int> ans;

    while (n) {
        ans.insert(n % base);
        n /= base;
    }
    return ans;
}

int solve(const int n) {
    int ans = 0;

    for (int x = 1; x <= n; ++x) {
        const auto d10 = digits(x, 10);
        const auto d8 = digits(x, 8);

        if (!d10.count(7) && !d8.count(7)) ++ans;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    cout << solve(n) << '\n';

    return 0;
}
