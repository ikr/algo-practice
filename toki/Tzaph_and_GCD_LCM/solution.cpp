#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<bool> sieve(const int n) {
    vector<bool> ans(n + 1, true);
    ans[0] = false;
    if (n) ans[1] = false;

    const int sq = sqrt(n);
    for (int i = 2; i <= sq; ++i) {
        if (!ans[i]) continue;
        for (int j = i * i; j <= n; j += i) ans[j] = false;
    }

    return ans;
}

ll mpow(const ll p, const ll x) {
    if (x == 0) return 1;
    if (x % 2) return p * mpow(p, x - 1);
    const ll sq = mpow(p, x / 2);
    return sq * sq;
}

vector<ll> factorize(const vector<bool> &primes, ll x) {
    vector<ll> ans;

    for (auto p = 0U; p < primes.size(); ++p) {
        if (!primes[p] || x % p) continue;

        int e = 0;
        while (x % p == 0) {
            ++e;
            x /= p;
        }

        ans.push_back(mpow(p, e));
        if (x == 1) break;
    }

    if (x != 1) ans.push_back(x);
    sort(begin(ans), end(ans));
    return ans;
}

pair<ll, ll> min_sum_split(const vector<ll> &factorization) {
    const int sz = factorization.size();
    if (sz == 1) return {1, factorization.front()};

    const ll prod = accumulate(cbegin(factorization), cend(factorization), 1LL,
                               multiplies<ll>{});

    return {prod / factorization.back(), factorization.back()};
}

pair<ll, ll> find_pair(const ll gcd_v, const ll lcm_v) {
    if (lcm_v % gcd_v) return {-1, -1};
    const ll rem = lcm_v / gcd_v;
    if (rem == 1) return {gcd_v, gcd_v};

    const auto [x, y] = min_sum_split(factorize(sieve(1e6), rem));
    return {x * gcd_v, y * gcd_v};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll gcd_v, lcm_v;
    cin >> gcd_v >> lcm_v;

    const auto [a, b] = find_pair(gcd_v, lcm_v);
    cout << a << ' ' << b << '\n';

    return 0;
}
