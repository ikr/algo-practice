#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int provably_innocent_num(const vector<vector<int>> &g) {
    const auto n = sz(g);
    vector<int> indeg(n, 0);

    for (int u = 0; u < n; ++u) {
        for (const auto v : g[u]) {
            ++indeg[v];
        }
    }

    return n - inof(count(cbegin(indeg), cend(indeg), 0));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, M, K;
        cin >> N >> M >> K;

        vector<vector<int>> g(N);
        for (int j = 1; j <= M; ++j) {
            int a, b;
            cin >> a >> b;
            --a;
            --b;

            g[a].push_back(b);
        }

        cout << "Case #" << i << ": " << provably_innocent_num(g) << '\n';
    }

    return 0;
}
