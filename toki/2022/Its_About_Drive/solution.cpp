#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool is_possible(const ll N, const ll F, const ll D) {
    const auto lo = F * (F + 1) / 2LL;
    const auto hi = [&]() -> ll {
        ll result{};
        for (ll i = 1; i <= N; ++i) {
            result += min(i, F + N - i);
        }
        return result;
    }();
    return lo <= D && D <= hi;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N, F, D;
    cin >> N >> F >> D;

    cout << (is_possible(N, F, D) ? "YES" : "NO") << '\n';
    return 0;
}
