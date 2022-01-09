#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool is_possible(const ll N, const ll F, const ll D) {
    if (F > N) return false;
    return (2 * F * F) <= (2 * D + N * N - N);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N, F, D;
    cin >> N >> F >> D;

    cout << (is_possible(N, F, D) ? "YES" : "NO") << '\n';
    return 0;
}
