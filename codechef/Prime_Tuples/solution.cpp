#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr int N_MAX = 1000000;

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

vector<int> primes_upto(const vector<bool> &prime) {
    const int n = prime.size();
    vector<int> ans(n, 0);
    for (int i = 1; i < n; ++i) {
        ans[i] = ans[i - 1] + (prime[i] ? 1 : 0);
    }
    return ans;
}

vector<ll> one_to_n_triplets_num(const int n) {
    vector<ll> ans(n + 1, 0);
    ans[3] = 1;
    for (int i = 4; i <= n; ++i) {
        const ll k = i - 1;
        ans[i] = ans[i - 1] + k * (k - 1LL) / 2LL;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    const auto prime = sieve(N_MAX);
    const auto pu = primes_upto(prime);
    const auto memo = one_to_n_triplets_num(N_MAX / 10);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << memo[pu[n]] << '\n';
    }

    return 0;
}
