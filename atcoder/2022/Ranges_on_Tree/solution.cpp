#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pair<int, int>> generate_intervals(const vvi &g) {
    vector<pair<int, int>> result(sz(g), {0, 0});
    int x{};
    const auto recur = [&](const auto &self, const int parent,
                           const int u) -> void {
        const auto children_num = count_if(
            cbegin(g[u]), cend(g[u]), [&](const int v) { return v != parent; });

        if (children_num == 0) {
            ++x;
            result[u] = {x, x};
            return;
        }

        for (const auto v : g[u]) {
            if (v == parent) continue;
            self(self, u, v);
        }

        int l = 1e9;
        int r = 0;

        for (const auto v : g[u]) {
            if (v == parent) continue;
            const auto [vl, vr] = result[v];
            l = min(l, vl);
            r = max(r, vr);
        }

        result[u] = {l, r};
    };

    recur(recur, -1, 0);
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vvi g(N);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (auto &row : g) {
        sort(begin(row), end(row));
    }

    for (const auto [l, r] : generate_intervals(g)) {
        cout << l << ' ' << r << '\n';
    }
    return 0;
}
