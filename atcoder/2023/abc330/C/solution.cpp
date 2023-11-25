#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<ll> squares(const ll lim) {
    vector<ll> ans;
    for (ll i = 1; i * i <= 2 * lim; ++i) {
        ans.push_back(i * i);
    }
    return ans;
}

ll min_value(const ll D) {
    if (D <= 2LL) return 0;
    const auto sq = squares(D);
    ll result = D;

    for (const auto a : sq) {
        const auto r = a - D;
        if (r == 0) return 0;

        if (r > 0) {
            result = min(result, r);
            continue;
        }

        const auto it = lower_bound(cbegin(sq), cend(sq), -r);
        if (it == cend(sq)) {
            result = min(result, r + *prev(cend(sq)));
            continue;
        }

        if (*it == -r) return 0;

        if (it == cbegin(sq)) {
            result = min({result, abs(r + *it), -r});
            continue;
        }

        result = min({result, abs(r + *prev(it)), abs(r + *it), -r});
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll D;
    cin >> D;
    cout << min_value(D) << '\n';
    return 0;
}
