#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

double solve(const int n) {
    vector<double> dp(n + 1, 2);
    for (int i = 3; i <= n; ++i) {
        const double q = 1.0 - doof(i - 1) / doof(i);
        return (doof(i - 1) * dp[i - 1] / doof(i)) / q;
    }

    return dp.back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(7) << fixed;

    int n;
    cin >> n;

    cout << solve(n) << '\n';
    return 0;
}
