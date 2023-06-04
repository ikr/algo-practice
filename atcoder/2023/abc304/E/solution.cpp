#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr pair<T, T> normalized(const pair<T, T> ab) {
    const auto [a, b] = ab;
    return {min(a, b), max(a, b)};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    atcoder::dsu uf(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        uf.merge(u, v);
    }

    set<pair<int, int>> ex;

    int K;
    cin >> K;

    for (int i = 0; i < K; ++i) {
        int x, y;
        cin >> x >> y;
        --x;
        --y;

        assert(!uf.same(x, y));
        ex.insert(normalized(pair{uf.leader(x), uf.leader(y)}));
    }

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; ++i) {
        int p, q;
        cin >> p >> q;
        --p;
        --q;

        const auto spoiling =
            ex.count(normalized(pair{uf.leader(p), uf.leader(q)}));
        cout << (spoiling ? "No" : "Yes") << '\n';
    }

    return 0;
}
