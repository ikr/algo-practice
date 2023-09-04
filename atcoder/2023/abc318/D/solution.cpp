#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_total_weight(const vector<vector<ll>> &g) {
    const auto n = sz(g);

    vector<vector<pii>> es_by_taken_v_bits(1 << n);
    for (int u = 0; u < n - 1; ++u) {
        for (int v = u + 1; v < n; ++v) {
            for (int bits = 0; bits < sz(es_by_taken_v_bits); ++bits) {
                if (bits & (1 << u)) continue;
                if (bits & (1 << v)) continue;
                es_by_taken_v_bits[bits].emplace_back(u, v);
            }
        }
    }

    ll result{};
    const auto recur = [&](const auto self, const ll weight,
                           const int v_bits) -> void {
        result = max(result, weight);
        for (const auto &[u, v] : es_by_taken_v_bits[v_bits]) {
            const auto v_bits_ = v_bits | (1 << u) | (1 << v);
            self(self, weight + g[u][v], v_bits_);
        }
    };

    recur(recur, 0LL, 0);
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<vector<ll>> g(N, vector(N, -1LL));
    for (int u = 0; u < N - 1; ++u) {
        for (int v = u + 1; v < N; ++v) {
            ll w;
            cin >> w;
            g[u][v] = w;
            g[v][u] = w;
        }
    }

    cout << max_total_weight(g) << '\n';
    return 0;
}
