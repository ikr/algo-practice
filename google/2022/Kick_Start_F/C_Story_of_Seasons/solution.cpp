#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

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
    map<pii, int> idx;
    for (const auto &[quantity, days_to_mature, price] : src) {
        idx.emplace(pii{days_to_mature, -price}, quantity);
    }

    ll result{};

    for (int d = 1; d < D && !idx.empty(); ++d) {
        int x = X;
        while (x && !idx.empty()) {
            auto it = idx.lower_bound(pii{D - d, INT_MIN});

            if (it != cend(idx) && it->first.first == D - d) {
                const auto [L, V_] = it->first;
                const auto Q = it->second;
                idx.erase(it);

                const auto taking = min(x, Q);
                x -= taking;
                if (taking < Q) idx.emplace(pii{L, V_}, Q - taking);
                result += 1LL * taking * (-1LL * V_);
            } else if (it == cbegin(idx)) {
                break;
            } else {

            }
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
