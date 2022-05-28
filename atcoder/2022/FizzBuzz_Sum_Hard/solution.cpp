#include <iostream>
#include <numeric>
using namespace std;

using ll = long long;

constexpr ll ar_sum(const ll a1, const ll n, const ll d) {
    return n * (2LL * a1 + (n - 1LL) * d) / 2LL;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N, A, B;
    cin >> N >> A >> B;

    const auto L = (A * B) / gcd(A, B);

    const auto ans = ar_sum(1, N, 1) - ar_sum(A, N / A, A) -
                     ar_sum(B, N / B, B) + ar_sum(L, N / L, L);

    cout << ans << '\n';
    return 0;
}
