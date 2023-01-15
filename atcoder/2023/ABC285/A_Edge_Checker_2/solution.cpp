#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    vector<set<int>> g(16);
    for (const auto &[u, v] : vector<pair<int, int>>{{1, 2},
                                                     {1, 3},
                                                     {2, 4},
                                                     {2, 5},
                                                     {3, 6},
                                                     {3, 7},
                                                     {4, 8},
                                                     {4, 9},
                                                     {5, 10},
                                                     {5, 11},
                                                     {6, 12},
                                                     {6, 13},
                                                     {7, 14},
                                                     {7, 15}}) {
        g[u].insert(v);
        g[v].insert(u);
    }

    int a, b;
    cin >> a >> b;

    cout << (g[a].count(b) ? "Yes" : "No") << '\n';
    return 0;
}
