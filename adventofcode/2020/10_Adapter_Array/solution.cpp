#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll count_ways(const vector<int> &xs) {
    const int n = xs.size();
    vector<ll> dp(n, 0);
    dp[0] = 1;

    for (int i = 1; i < n; ++i) {
        for (const int j : {i - 1, i - 2, i - 3}) {
            if (j >= 0 && xs[i] - xs[j] <= 3) dp[i] += dp[j];
        }
    }

    return dp.back();
}

int main() {
    vector<int> xs{0};
    for (string line; getline(cin, line);) {
        xs.push_back(stoi(line));
    }
    sort(begin(xs), end(xs));
    xs.push_back(xs.back() + 3);

    cout << count_ways(xs) << '\n';
    return 0;
}
