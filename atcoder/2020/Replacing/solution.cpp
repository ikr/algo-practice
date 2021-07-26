#include <bits/stdc++.h>
using namespace std;
using ll = long long;

unordered_map<ll, int> count_values(const vector<ll> &xs) {
    unordered_map<ll, int> ans;
    for (const auto &x : xs) ++ans[x];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vector<ll> xs(sz, 0LL);
    for (auto &x : xs) cin >> x;
    ll s = accumulate(xs.cbegin(), xs.cend(), 0LL);

    auto cnt = count_values(xs);

    int q;
    cin >> q;

    while (q--) {
        int b, c;
        cin >> b >> c;
        const int d = b - c;
        s -= cnt[b] * d;
        cnt[c] += cnt[b];
        cnt[b] = 0;

        cout << s << '\n';
    }

    return 0;
}
