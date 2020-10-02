#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll first_day_free(const vector<int> &xs, const int k) {
    ll balance = 0;
    ll day = 0;

    for (const auto x : xs) {
        ++day;
        balance += x;
        if (balance < k) return day;
        balance -= k;
    }

    return day + balance / k + 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> xs(n, 0);
        for (auto &x : xs) cin >> x;
        cout << first_day_free(xs, k) << '\n';
    }

    return 0;
}
