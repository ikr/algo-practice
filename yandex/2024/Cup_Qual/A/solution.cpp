#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr ll Inf = LONG_LONG_MAX;
static constexpr ll Lim = 1'000'000'000ULL * 1'000'000'000ULL;

using ulll = __uint128_t;

template <typename T> constexpr ulll ulllof(const T x) {
    return static_cast<ulll>(x);
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

ll nth_num(const ll a, const ll b, const ll c, const ll n) {
    priority_queue<ulll> xs;
    for (const auto &[m, k] :
         {pair{lcm(a, b), c}, pair{lcm(b, c), a}, pair{lcm(a, c), b}}) {
    }

    return Inf;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll a, b, c, n;
    cin >> a >> b >> c >> n;

    const auto result = nth_num(a, b, c, n);
    if (result <= Lim) {
        cout << result << '\n';
    } else {
        cout << "-1\n";
    }
    return 0;
}
