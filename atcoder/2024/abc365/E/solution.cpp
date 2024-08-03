#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<ll> xs(n);
    for (auto &x : xs) cin >> x;

    vector<ll> ss(n, xs.back());
    for (int i = n - 2; i >= 0; --i) ss[i] = xs[i] ^ ss[i - 1];

    const auto sub = [&](const int i, const int j) -> ll {
        return (j == n - 1) ? ss[i] : (ss[i] ^ ss[i + 1]);
    };

    return 0;
}
