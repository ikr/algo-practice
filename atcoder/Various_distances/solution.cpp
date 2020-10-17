#include <bits/stdc++.h>
using namespace std;
using ll = long long;

tuple<ll, double, int> dists(const vector<int> &xs) {
    ll m = 0;
    ll esq = 0;
    int c = -1e9;

    for (const int x : xs) {
        m += abs(x);
        esq += x * static_cast<ll>(x);
        c = max(abs(x), c);
    }

    return {m, sqrt(static_cast<double>(esq)), c};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(10) << fixed;

    int n;
    cin >> n;
    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;

    const auto [m, e, c] = dists(xs);
    cout << m << '\n' << e << '\n' << c << '\n';
    return 0;
}
