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
    ll days_to_mature;
    int price;
};

ll max_revenue(const ll D, const int X, const vector<Seedable> &src) {
    // L -> (V Q)
    map<ll, vector<pii>> idx;

    for (const auto &[quantity, days_to_mature, price] : src) {
        idx[days_to_mature].emplace_back(price, quantity);
    }

    // (V Q)
    priority_queue<pii> stash;

    ll result{};
    ll d = D;

    while (d > 0 && !(idx.empty() && stash.empty())) {
        const auto cur_L = D - d;

        if (!idx.empty() && cbegin(idx)->first == cur_L) {
            for (const auto &[V, Q] : cbegin(idx)->second) {
                stash.emplace(V, Q);
            }
            idx.erase(cbegin(idx));
        }

        auto cap = X;

        while (!stash.empty() && cap > 0) {
            const auto [V, Q] = stash.top();
            stash.pop();

            const auto utilized = min(cap, Q);
            cap -= utilized;
            result += 1LL * utilized * V;

            if (Q - utilized > 0) {
                stash.emplace(V, Q - utilized);
                assert(cap == 0);
            }
        }

        if (stash.empty()) {
            if (!idx.empty()) {
                d = D - cbegin(idx)->first;
            }
            continue;
        }

        assert(cap == 0);
        --d;
    }

    return result;
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

        cout << "Case #" << i << ": " << max_revenue(D, X, src) << '\n';
    }

    return 0;
}
