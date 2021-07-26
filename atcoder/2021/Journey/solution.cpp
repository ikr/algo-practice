#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

double solve(const int n) {
    double ans = 0.0;

    for (int i = 1; i < n; ++i) {
        ans += doof(n) / doof(n - i);
    }

    return ans;
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
