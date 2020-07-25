#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<bool> mono_indicators(const vector<int> xs, const int K) {
    const int sz = xs.size();
    ll prod = accumulate(xs.cbegin(), xs.cbegin() + K, 1LL, multiplies<ll>{});
    vector<bool> ans;

    for (int i = K; i < sz; ++i) {
        ll prod_prime = (prod / xs[i - K]) * xs[i];
        ans.push_back(prod_prime > prod ? true : false);
        prod = prod_prime;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, K;
    cin >> N >> K;
    vector<int> xs(N, 0);
    for (auto &x : xs) cin >> x;

    const auto ans = mono_indicators(xs, K);
    for (const bool m : ans) {
        cout << (m ? "Yes" : "No") << '\n';
    }

    return 0;
}
