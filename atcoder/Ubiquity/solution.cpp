#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll M = 1e9 + 7;

ll m_exp(const ll x, const int p) {
    if (p == 0) return 1;
    if (p % 2) return (x * m_exp(x, p - 1)) % M;
    const ll sq = m_exp(x, p / 2);
    return (sq * sq) % M;
}

int solve(const ll n) {
    if (n < 2) return 0;
    if (n == 2) return 2;

    const ll total = m_exp(10, n);
    const ll nones = m_exp(8, n);
    const ll ones = (n * m_exp(8, n - 1)) % M;

    return (((total - nones - 2 * ones) % M) + M) % M;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    cout << solve(n) << '\n';

    return 0;
}
