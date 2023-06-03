#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr ll sq(const ll x) { return x * x; };

constexpr bool are_adjacent(const ll D, const pair<ll, ll> &a,
                            const pair<ll, ll> &b) {
    const auto [ax, ay] = a;
    const auto [bx, by] = b;
    return sq(ax - bx) + sq(ay - by) <= sq(D);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    ll D;
    cin >> D;

    vector<pair<ll, ll>> P(N);
    for (auto &[x, y] : P) cin >> x >> y;

    atcoder::dsu uf(N);

    for (int i = 0; i < N - 1; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (are_adjacent(D, P[i], P[j])) {
                uf.merge(i, j);
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        const auto ans = uf.same(0, i) ? "Yes" : "No";
        cout << ans << '\n';
    }

    return 0;
}
