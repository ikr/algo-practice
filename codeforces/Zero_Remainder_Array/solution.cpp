#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using ummi = unordered_multimap<int, int>;

int count_moves(const int k, const vi &xs) {
    ummi xs_by_rem;
    for (const auto x : xs) {
        if (x % k) {
            xs_by_rem.emplace(x % k, x);
        }
    }

    if (xs_by_rem.empty()) return 0;

    int ans = 1;

    for (int x = 1; !xs_by_rem.empty(); ++x, ++ans) {
        const int d = k - (x % k);
        if (xs_by_rem.count(d)) {
            const auto it = xs_by_rem.find(d);
            xs_by_rem.erase(it);
        }
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
