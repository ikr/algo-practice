#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, D;
    ll P;
    cin >> N >> D >> P;

    vector<ll> F(N);
    for (auto &x : F) cin >> x;
    sort(rbegin(F), rend(F));

    while (sz(F) % D) F.push_back(0LL);

    vector<ll> ss(sz(F));
    partial_sum(cbegin(F), cend(F), begin(ss));

    ll batches_to_take{};
    for (ll k = 1; D * k - 1 < sz(F); ++k) {
        if (P >= (ss[D * k - 1] - (k > 1 ? ss[D * (k - 1) - 1] : 0LL))) {
            break;
        }
        batches_to_take = k;
    }

    ll ans = P * batches_to_take;
    ans += ss.back() - (batches_to_take ? ss[D * batches_to_take - 1] : 0LL);
    cout << ans << '\n';
    return 0;
}
