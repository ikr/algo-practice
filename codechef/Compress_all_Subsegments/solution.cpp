#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Iter = vector<int>::const_iterator;
static constexpr ll M = 998244353;

ll compute_f(const Iter first, const Iter last) {
    const int s = accumulate(first + 1, last, *first,
                             [](const int x, const int y) { return x ^ y; });
    const int p = log2(s);
    return 1 << p;
}

ll sum_of_fs(const vector<int> &xs) {
    const int n = xs.size();
    ll ans = accumulate(cbegin(xs), cend(xs), 0LL,
                        [](const ll x, const ll y) { return (x + y) % M; });

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ans += compute_f(cbegin(xs) + i, cbegin(xs) + j + 1);
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;

    cout << sum_of_fs(xs) << '\n';
    return 0;
}
