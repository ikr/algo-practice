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

    int n;
    cin >> n;

    vector<ll> deltas(n);
    for (auto &x : deltas) {
        cin >> x;
    }

    vector<ll> locs(sz(deltas) + 1, 0LL);
    partial_sum(cbegin(deltas), cend(deltas), begin(locs) + 1);
    locs.push_back(locs.back());

    vector<ll> pmin(sz(locs));
    inclusive_scan(cbegin(locs), cend(locs), begin(pmin), ranges::min);

    vector<ll> pmax(sz(locs));
    inclusive_scan(cbegin(locs), cend(locs), begin(pmax), ranges::max);

    vector<ll> smin(sz(locs));
    inclusive_scan(rbegin(locs), rend(locs), rbegin(smin), ranges::min);

    vector<ll> smax(sz(locs));
    inclusive_scan(rbegin(locs), rend(locs), rbegin(smax), ranges::max);

    ll result = pmax.back() - pmin.back() + 1;

    for (int i = 0; i != n; ++i) {
        const ll shift = -2LL * deltas[i];
        const int j = i + 1;

        const ll left_lo = pmin[j - 1];
        const ll left_hi = pmax[j - 1];
        const ll right_lo = smin[j + 1] + shift;
        const ll right_hi = smax[j + 1] + shift;

        for (const ll lo : {left_lo, right_lo}) {
            for (const ll hi : {left_hi, right_hi}) {
                result = max(result, hi - lo + 1);
            }
        }
    }

    cout << result << '\n';
    return 0;
}
