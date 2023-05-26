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

    int n, k;
    cin >> n >> k;

    deque<ll> xs(n);
    for (auto &x : xs) cin >> x;
    sort(begin(xs), end(xs));

    for (int i = 1; i <= k; ++i) {
        if (sz(xs) < 2) {
            xs.pop_back();
            continue;
        }

        if (xs[0] + xs[1] <= xs.back()) {
            xs.pop_front();
            xs.pop_front();
        } else {
            xs.pop_back();
        }
    }

    cout << accumulate(cbegin(xs), cend(xs), 0LL) << '\n';
    return 0;
}
