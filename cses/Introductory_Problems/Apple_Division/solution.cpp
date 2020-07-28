#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using ll = long long;

static constexpr int MAX_N = 20;

ll min_diff(const vi &xs) {
    const int sz = xs.size();
    const ll total = accumulate(xs.cbegin(), xs.cend(), 0LL);

    ll ans = INT_MAX;
    for (int b = 0; b <= (1 << sz) - 1; ++b) {
        const bitset<MAX_N> bits(b);
        ll s = 0;
        for (int i = 0; i != sz; ++i) {
            if (bits[i]) s += xs[i];
        }

        ans = min(ans, abs(total - s - s));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vi xs(sz, 0);
    for (auto &x : xs) cin >> x;

    cout << min_diff(xs) << '\n';
    return 0;
}
