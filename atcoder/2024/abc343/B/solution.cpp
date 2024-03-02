#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> inc_all(vector<int> xs) {
    for (auto &x : xs) ++x;
    return xs;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<vector<int>> M(N, vector<int>(N, 0));
    for (auto &row : M) {
        for (auto &x : row) cin >> x;
    }

    vector<vector<int>> g(N);
    for (int u = 0; u < N; ++u) {
        for (int v = 0; v < N; ++v) {
            if (M[u][v]) {
                g[u].push_back(v);
            }
        }
        sort(begin(g[u]), end(g[u]));
    }

    for (const auto &row : g) {
        cout << inc_all(row) << '\n';
    }
    return 0;
}
