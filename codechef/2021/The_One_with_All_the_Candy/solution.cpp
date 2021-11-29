#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_duration(const vi &xs) {
    const auto zs = inof(count(cbegin(xs), cend(xs), 0));
    if (zs) return sz(xs) - zs;

    const auto it = upper_bound(cbegin(xs), cend(xs), xs[0]);
    if (it == cend(xs)) return llof(xs[0]) * sz(xs);

    return llof(xs[0]) * sz(xs) + distance(it, cend(xs));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        cout << max_duration(xs) << '\n';
    }

    return 0;
}
