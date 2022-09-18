#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

struct Seedable final {
    int quantity;
    int days_to_mature;
    int price;
};

ll max_revenue(const int D, const int X, vector<Seedable> src) {
    assert(X == 1);
    sort(begin(src), end(src),
         [](const auto &a, const auto &b) { return a.price > b.price; });

    ll result{};
    for (int d = D - 1; d >= 1; --d) {
        for (auto &[quantity, days_to_mature, price] : src) {
            if (!quantity || days_to_mature > (D - d)) continue;
            --quantity;
            result += price;
            break;
        }
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int D, N, X;
        cin >> D >> N >> X;

        vector<Seedable> src(N);
        for (auto &[quantity, days_to_mature, price] : src) {
            cin >> quantity >> days_to_mature >> price;
        }

        cout << "Case #" << i << ": " << max_revenue(D, X, move(src)) << '\n';
    }

    return 0;
}
