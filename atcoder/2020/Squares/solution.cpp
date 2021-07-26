#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 1e9 + 7;

constexpr ll m_sq(const ll x) { return (x * x) % M; }

ll solve(const ll n, const ll a, const ll b) {
    assert(a <= b);

    const ll indep = (m_sq(n - a + 1) * m_sq(n - b + 1)) % M;
    const ll cross = (m_sq(n - b + 1) *
                      (m_sq(b - a + 1) + 2 * (b * (a - 1) + a * (a - 1) / 2))) %
                     M;
    return (indep - cross + M) % M;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        ll n, a, b;
        cin >> n >> a >> b;
        cout << solve(n, min(a, b), max(a, b)) << '\n';
    }

    return 0;
}
