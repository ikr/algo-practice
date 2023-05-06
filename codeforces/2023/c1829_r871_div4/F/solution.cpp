#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<int, int> derive_x_y(const vector<int> &deg) {
    const int L = inof(count(cbegin(deg), cend(deg), 1));
    const auto V = sz(deg);

    const auto x = V - L - 1;
    const auto y = L / (V - L - 1);
    return {x, y};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<int> deg(n, 0);

        for (int i = 1; i <= m; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;

            ++deg[u];
            ++deg[v];
        }

        sort(begin(deg), end(deg));
        const auto [x, y] = derive_x_y(deg);
        cout << x << ' ' << y << '\n';
    }

    return 0;
}
