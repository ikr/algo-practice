#include <bits/stdc++.h>
using namespace std;
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

vector<int> gather_ps(const vector<bool> &prime) {
    const int sz = prime.size();
    vector<int> ans;
    ans.reserve(sz / 10);

    for (int i = 2; i < sz; ++i) {
        if (prime[i]) ans.push_back(i);
    }

    return ans;
}

vector<int> prime_sums_of_two_primes(const vector<bool> &prime,
                                     const vector<int> &ps) {
    const int k = ps.size();
    vector<int> ans;
    ans.reserve(k / 8);

    for (int i = 1; i < k - 2; ++i) {
        const int c = 2 + ps[i];
        if (prime[c]) ans.push_back(c);
    }

    return ans;
}

int triples_num(const vector<int> &pss, const int n) {
    const auto it = upper_bound(cbegin(pss), cend(pss), n);
    return distance(cbegin(pss), it);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    const auto prime = sieve(N_MAX);
    const auto ps = gather_ps(prime);
    const auto pss = prime_sums_of_two_primes(prime, ps);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << triples_num(pss, n) << '\n';
    }

    return 0;
}
