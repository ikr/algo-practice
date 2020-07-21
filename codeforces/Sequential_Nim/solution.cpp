#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

bool first_wins(const vi &xs) {
    const int sz = xs.size();
    vector<bool> dp(sz, true);

    for (int i = sz - 2; i >= 0; --i) {
        const int x = xs[i];
        if (x == 1) dp[i] = !dp[i + 1];
    }

    return dp.front();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int sz;
        cin >> sz;
        vi xs(sz, 0);
        for (auto &x : xs) cin >> x;

        cout << (first_wins(xs) ? "First" : "Second") << '\n';
    }

    return 0;
}
