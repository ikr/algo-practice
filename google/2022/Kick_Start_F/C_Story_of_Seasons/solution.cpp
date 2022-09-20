#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

struct Seedable final {
    int quantity;
    ll days_to_mature;
    int price;
};

struct Sowing final {
    pair<ll, ll> days_interval;
    int day_capacity;
};

ll max_revenue(const ll D, const int X, vector<Seedable> src) {
    sort(begin(src), end(src), [](const auto &a, const auto &b) {
        return tuple{-a.days_to_mature, a.price, a.quantity} <
               tuple{-b.days_to_mature, b.price, b.quantity};
    });

    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        ll D;
        int N, X;
        cin >> D >> N >> X;

        vector<Seedable> src(N);
        for (auto &[quantity, days_to_mature, price] : src) {
            cin >> quantity >> days_to_mature >> price;
        }

        cout << "Case #" << i << ": " << max_revenue(D, X, move(src)) << '\n';
    }

    return 0;
}
