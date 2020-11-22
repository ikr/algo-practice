#include <bits/stdc++.h>
#include <numeric>
using namespace std;

double solve(const vector<double> &xs) {
    const int n = xs.size();
    vector<double> ss(n + 1, 0);
    partial_sum(cbegin(xs), cend(xs), next(begin(ss)));

    double acc = 0;

    for (int i = 0; i < n - 1; ++i) {
        acc += ss[i + 1];
        acc += ss[n] - ss[i + 1];
    }

    return ss[n] + acc / (n - 1.0);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(7) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;
        vector<double> xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << "Case #" << i << ": " << solve(xs) << '\n';
    }

    return 0;
}
