#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr ll M = 1'000'000'007;

ll sum_of_ands(const ll n) {
    array<ll, 63> fs{};
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int T;
    cin >> T;
    while (T--) {
        ll n;
        cin >> n;
        cout << sum_of_ands(n) << '\n';
    }

    return 0;
}
