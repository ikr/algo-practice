#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll max_xor(vector<ll> &xs) {
    map<ll, int> counts;
    for (const auto x : xs) ++counts[x];

    ll to_flip = -1;

    for (auto it = counts.crbegin(); it != counts.crend(); ++it) {
        if (it->second % 2 == 0) {
            to_flip = it->first;
            break;
        }
    }

    ll ans = 0;
    for (const auto x : xs) {
        if (x == to_flip) {
            to_flip = -1;
        } else {
            ans ^= x;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vector<ll> xs(sz, 0);
    for (auto &x : xs) cin >> x;

    cout << max_xor(xs) << '\n';
    return 0;
}
