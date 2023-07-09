#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> gather_children(const vector<int> &ps) {
    vector<vector<int>> ch(sz(ps));

    for (int i = 0; i < sz(ps); ++i) {
        if (ps[i] == i) continue;
        ch[ps[i]].push_back(i);
    }

    return ch;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<int> P(N, 0);
    for (int i = 1; i < N; ++i) {
        cin >> P[i];
        --P[i];
    }

    vector<int> coverage(N, 0);
    for (int i = 0; i < M; ++i) {
        int x, y;
        cin >> x >> y;
        coverage[x - 1] = max(coverage[x - 1], y + 1);
    }

    const auto chi = gather_children(P);
    int ans{};

    const auto recur = [&](const auto self, const int c, const int u) -> void {
        if (c > 0) ++ans;
        for (const auto v : chi[u]) {
            self(self, max(max(c - 1, 0), coverage[v]), v);
        }
    };

    recur(recur, coverage[0], 0);
    cout << ans << '\n';
    return 0;
}
