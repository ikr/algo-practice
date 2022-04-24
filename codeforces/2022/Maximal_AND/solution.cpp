#include <array>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll best_shot(const vector<ll> &xs, const ll k) {
    array<int, 31> fs{};
    fs.fill(0);

    for (const auto x : xs) {
        for (int i = 0; i < sz(fs); ++i) {
            if ((1LL << i) & x) ++fs[i];
        }
    }

    priority_queue<pii> q;
    for (int i = 0; i < sz(fs); ++i) {
        q.emplace(i, fs[i]);
    }

    ll curr = k;
    ll result{};

    while (!q.empty()) {
        const auto [i, m] = q.top();
        q.pop();
        const auto diff = llof(sz(xs)) - m;
        if (diff > curr) continue;

        result |= (1LL << i);
        curr -= min(curr, diff);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        ll k;
        cin >> k;

        vector<ll> xs(n);
        for (auto &x : xs) cin >> x;

        cout << best_shot(xs, k) << '\n';
    }

    return 0;
}
