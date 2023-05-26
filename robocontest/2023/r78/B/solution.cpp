#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(5) << fixed;

    double x, pw, pw_;
    cin >> x >> pw >> pw_;

    pw /= 100.0;
    pw_ /= 100.0;

    const auto x_ = (1.0 - pw) * x / (1.0 - pw_);
    cout << x_ << '\n';
    return 0;
}
