#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using mi = map<int, int>;
using ll = long long;

void dec(mi &m, const mi::iterator it) {
    --(it->second);
    if (!it->second) m.erase(it);
}

ll count_moves(const int k, const vi &xs) {
    mi counts_by_m;
    for (const auto x : xs) {
        if (x % k == 0) continue;
        ++counts_by_m[x % k];
    }
    if (counts_by_m.empty()) return 0;

    ll ans = 1;

    while (!counts_by_m.empty()) {
        const ll d = k - ans % k;
        auto it = counts_by_m.lower_bound(d);

        if (it != counts_by_m.end() && it->first == d) {
            ++ans;
        } else {
            if (it != counts_by_m.begin()) --it;
            ans += k - (ans % k + it->first) % k + 1;
        }

        dec(counts_by_m, it);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int sz, k;
        cin >> sz >> k;
        vi xs(sz, 0);
        for (auto &x : xs) cin >> x;

        cout << count_moves(k, xs) << '\n';
    }

    return 0;
}
