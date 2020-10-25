#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll log(const long double b, const long double x) { return log(x) / log(b); }

vector<ll> multiples(const ll x, const ll lim) {
    const ll lim_exp = log(x, lim) + 1;
    vector<ll> ans(lim_exp, 1);
    for (ll i = 1; i < lim_exp; ++i) {
        ans[i] = x * ans[i - 1];
    }
    return ans;
}

pair<ll, ll> solve(const ll n) {
    const auto ts = multiples(3, n);
    const auto fs = multiples(5, n);

    for (auto i = 1U; i < fs.size(); ++i) {
        if (fs[i] >= n || n - fs[i] == 1) return {-1, -1};

        const auto it = equal_range(cbegin(ts), cend(ts), n - fs[i]).first;
        if (it != cend(ts) && *it == n - fs[i]) {
            return {distance(cbegin(ts), it), i};
        }
    }

    return {-1, -1};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin >> n;
    const auto [a, b] = solve(n);
    cout << a;
    if (b != -1) {
        cout << ' ' << b;
    }
    cout << '\n';

    return 0;
}
