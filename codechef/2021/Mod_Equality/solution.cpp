#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_ops(const vi &xs) {
    const auto lo = *min_element(cbegin(xs), cend(xs));
    const auto num = inof(count(cbegin(xs), cend(xs), lo));
    if (lo == 0) return sz(xs) - num;

    for (const auto x : xs) {
        if (lo == x) continue;
        if (x - lo > lo) continue;
        return sz(xs);
    }

    return sz(xs) - num;
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

        cout << min_ops(xs) << '\n';
    }

    return 0;
}
