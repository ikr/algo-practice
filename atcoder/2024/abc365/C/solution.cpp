#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr ll Inf = 1e16;

bool is_ok(const vector<int> &xs, const ll m, const ll sub_lim) {
    ll cur{};
    for (const auto &x : xs) cur += min(x + 0LL, sub_lim);
    return cur <= m;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    ll m;
    cin >> m;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    if (is_ok(xs, m, Inf)) {
        cout << "infinite\n";
    } else {
        ll lo{};
        ll hi{Inf};

        while (lo + 1 < hi) {
            const auto x = midpoint(lo, hi);
            if (is_ok(xs, m, x)) {
                lo = x;
            } else {
                hi = x;
            }
        }

        cout << lo << "\n";
    }

    return 0;
}
