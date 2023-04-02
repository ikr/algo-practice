#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll div_ceil(const ll x, const ll y) {
    return x ? (x + y - 1LL) / y : 0LL;
}

ll find_X(const ll N, const ll M) {
    ll ans = LONG_LONG_MAX;

    for (ll a = 1; a * a <= M; ++a) {
        const auto b = div_ceil(M, a);
        if (a <= N && b <= N && a * b >= M) ans = min(ans, a * b);
    }

    return ans == LONG_LONG_MAX ? -1LL : ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N, M;
    cin >> N >> M;
    cout << find_X(N, M) << '\n';
    return 0;
}
