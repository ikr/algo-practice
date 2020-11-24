#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 1e9 + 7;

ll mpow(const ll x, const int p) {
    if (p == 0) return 1;
    if (p % 2) return (x * mpow(x, p - 1)) % M;
    const ll sq = mpow(x, p / 2);
    return (sq * sq) % M;
}

ll cute_count(const ll n, const ll m) {
    if (n == 1) return 1;
    if (m == 1) return 0;

    vector<ll> m_last(n, 1);
    vector<ll> not_m_last(n, m - 1);

    for (int i = 1; i < n; ++i) {
        m_last[i] = not_m_last[i - 1];

        not_m_last[i] =
            (((not_m_last[i - 1] + m_last[i - 1]) % M) * (m - 1)) % M;
    }

    return (m_last.back() + not_m_last.back() - mpow(m - 1, n) + M) % M;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, m;
    cin >> n >> m;
    cout << cute_count(n, m) << '\n';

    return 0;
}
