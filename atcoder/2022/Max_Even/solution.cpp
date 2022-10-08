#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_even_sum(vector<int> xs) {
    sort(begin(xs), end(xs));
    optional<int> ev_hi;
    optional<int> od_hi;

    ll ans = -1;

    for (const auto x : xs) {
        if (x % 2 == 0) {
            if (ev_hi) {
                ans = max(ans, 0LL + *ev_hi + x);
            }
            ev_hi = x;
        } else {
            if (od_hi) {
                ans = max(ans, 0LL + *od_hi + x);
            }
            od_hi = x;
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    cout << max_even_sum(move(xs)) << '\n';
    return 0;
}
