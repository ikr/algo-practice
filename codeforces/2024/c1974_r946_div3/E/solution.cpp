#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_happiness(const ll sal, const ll c0, const int h0,
                  const vector<pair<ll, int>> &xs) {
    const auto guaranteed = c0 == 0LL ? h0 : 0;
    if (empty(xs)) return guaranteed;

    const auto hi = 2LL * accumulate(cbegin(xs), cend(xs), 0,
                                     [](const ll acc, const auto ch) {
                                         return acc + ch.first;
                                     });
    const auto cap = [hi](const ll c) -> ll { return c <= hi ? c : hi; };

    unordered_map<ll, int> g0;
    g0.emplace(0, guaranteed);

    for (const auto &[c, h] : xs) {
        unordered_map<ll, int> g1;

        for (const auto &[rest, gathered_health] : g0) {
            if (rest + sal >= c) {
                g1[cap(rest + sal - c)] =
                    max(g1[cap(rest + sal - c)], gathered_health + h);
            }
            g1[cap(rest + sal)] = max(g1[cap(rest + sal)], gathered_health);
        }

        g0 = g1;
    }

    return max_element(cbegin(g0), cend(g0),
                       [](const auto kv0, const auto kv1) {
                           return kv0.second < kv1.second;
                       })
        ->second;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int m;
        cin >> m;

        ll sal;
        cin >> sal;

        ll c0;
        cin >> c0;

        int h0;
        cin >> h0;

        vector<pair<ll, int>> xs;
        for (int j = 1; j < m; ++j) {
            ll c;
            int h;
            cin >> c >> h;
            xs.emplace_back(c, h);
        }

        cout << max_happiness(sal, c0, h0, xs) << '\n';
    }

    return 0;
}
