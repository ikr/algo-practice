#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> children(const vector<int> &P) {
    vector<vector<int>> result(sz(P));
    for (int u = 0; u < sz(P); ++u) {
        if (P[u] >= 0) result[P[u]].push_back(u);
    }
    return result;
}

ll max_fun(const vector<int> &F, const vector<int> &P) {
    const auto ch = children(P);
    vector<ll> fun(sz(P), 0);

    const auto recur = [&](const auto self, const int u) -> void {
        if (ch[u].empty()) {
            fun[u] = F[u];
        } else {
            for (const auto v : ch[u]) self(self, v);

            const auto s = accumulate(
                cbegin(ch[u]), cend(ch[u]), 0LL,
                [&](const ll agg, const int i) { return agg + fun[i]; });

            for (int i = 0; i < sz(ch[u]); ++i) {
                fun[u] = max(fun[u], max(fun[ch[u][i]], llof(F[u])) + s -
                                         fun[ch[u][i]]);
            }
        }
    };

    ll result{};
    for (int i = 0; i < sz(P); ++i) {
        if (P[i] < 0) {
            recur(recur, i);
            result += fun[i];
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
        int N;
        cin >> N;

        vector<int> F(N);
        for (auto &f : F) cin >> f;

        vector<int> P(N);
        for (auto &p : P) {
            cin >> p;
            --p;
        }

        cout << "Case #" << i << ": " << max_fun(F, P) << '\n';
    }

    return 0;
}
