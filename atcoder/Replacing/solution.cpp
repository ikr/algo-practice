#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vector<ll> xs(sz, 0LL);
    for (auto &x : xs) cin >> x;
    ll s = accumulate(xs.cbegin(), xs.cend(), 0LL);

    unordered_map<ll, vector<int>> indices_by_value;
    for (int i = 0; i < sz; ++i) {
        indices_by_value[xs[i]].push_back(i);
    }

    int q;
    cin >> q;

    while (q--) {
        int b, c;
        cin >> b >> c;
        int d = b - c;

        for (auto i : indices_by_value[b]) {
            s -= d;
            xs[i] = c;
            indices_by_value[c].push_back(i);
        }
        indices_by_value[b] = {};

        cout << s << '\n';
    }

    return 0;
}
