#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll integer_sqrt_floor(const ll x) {
    ll result{};
    for (ll k = 1LL << 30; k != 0LL; k /= 2LL) {
        if ((result + k) * (result + k) <= x) {
            result += k;
        }
    }
    return result;
}

int decomposition_size(const ll n) {
    vector<ll> asq;
    asq.reserve(integer_sqrt_floor(n));
    for (ll k = 1; k * (k + 1) <= n; ++k) asq.push_back(k * (k + 1));

    if (binary_search(cbegin(asq), cend(asq), n)) return 1;

    for (const auto a : asq) {
        const auto b = n - a;
        assert(b > 0LL);
        if (binary_search(cbegin(asq), cend(asq), b)) return 2;
    }

    return 3;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n;
    cin >> n;

    cout << decomposition_size(n) << '\n';
    return 0;
}
