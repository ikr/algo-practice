#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<ll> xs(N);
    for (auto &x : xs) cin >> x;
    sort(begin(xs), end(xs));

    vector<ll> ys(N);
    for (auto &y : ys) cin >> y;
    sort(begin(ys), end(ys));

    ll result = LONG_LONG_MAX;

    for (const auto x : xs) {
        auto it = lower_bound(xbegin(ys), xend(ys), x);
        auto jt = (it == xbegin(ys)) ? it : prev(it);
        if (it == xend(ys)) it = jt;

        result = min({result, abs(x - *it), abs(x - *jt)});
    }

    cout << result << '\n';
    return 0;
}
