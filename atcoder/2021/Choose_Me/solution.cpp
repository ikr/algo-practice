#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int min_speeches(vector<pair<ll, ll>> xys) {
    ll total_a =
        accumulate(cbegin(xys), cend(xys), 0LL,
                   [](const ll agg, const auto &ab) { return agg + ab.first; });

    sort(begin(xys), end(xys), [](const auto &lhs, const auto &rhs) {
        return 2LL * lhs.first + lhs.second > 2LL * rhs.first + rhs.second;
    });

    const int n = xys.size();
    ll total_b = 0LL;

    for (int i = 0; i < n; ++i) {
        const auto [a, b] = xys[i];
        total_b += a + b;
        total_a -= a;
        if (total_b > total_a) return i + 1;
    }

    return n;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pair<ll, ll>> xys(n);
    for (auto &[a, b] : xys) {
        cin >> a >> b;
    }

    cout << min_speeches(move(xys)) << '\n';
    return 0;
}
