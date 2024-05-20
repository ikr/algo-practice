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
    const ll n = sz(xs);

    int result{};
    ll rem = sal * n;
    if (rem >= xs.back().first) {
        result += xs.back().second;

        rem = (sal >= xs.back().first) ? (sal * (n - 1))
                                       : (rem - sal - xs.back().first);
    }

    for (int i = n - 2; i >= 0; --i) {
    }

    return result;
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
