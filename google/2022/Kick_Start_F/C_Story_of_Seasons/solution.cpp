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

struct Sowing final {
    pair<ll, ll> days_interval;
    int day_capacity;
};

ll max_revenue(const ll D, const int X, vector<Seedable> src) {
    // L -> (V Q)
    map<ll, priority_queue<pii>> idx;

    for (const auto &[quantity, days_to_mature, price] : src) {
        idx[days_to_mature].emplace(price, quantity);
    }

    // (V Q)
    priority_queue<pii> stash;

    ll result{};
    ll cur = D;

    while (cur > 0 && !(idx.empty() && stash.empty())) {
        const auto cur_L = D - cur;

        if (!idx.empty() && cbegin(idx)->first == cur_L) {
            while (!(cbegin(idx)->second.empty())) {
                stash.push(cbegin(idx)->second.top());
                begin(idx)->second.pop();
            }
            idx.erase(cbegin(idx));
        }

        auto r_Q = X;

        while (!stash.empty() && r_Q) {
            const auto [V, Q] = stash.top();
            stash.pop();

            const auto utilized = min(r_Q, Q);
            r_Q -= utilized;
            result += 1LL * utilized * V;

            if (Q - utilized > 0) {
                stash.emplace(V, Q - utilized);
                assert(r_Q == 0);
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
