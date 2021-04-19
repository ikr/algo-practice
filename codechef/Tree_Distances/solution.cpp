#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

optional<int> isqrt(const int x) {
    const int q = inof(sqrt(x));
    return q * q == x ? optional{q} : nullopt;
}

optional<int> odd_levels_occupancy(const int y, const int n) {
    assert(y > 0);

    for (int i = 1; i < n; i++) {
        if (2 * i * (n - i) == y) return i;
    }

    return nullopt;
}

pair<int, vector<pii>> construct_tree(const int n, const int olo) {
    vector<pii> es;
    es.reserve(n - 1);

    for (int i = 1; i <= olo; ++i) es.emplace_back(1, 1 + i);

    const int elo = n - olo;
    for (int i = 1; i <= elo - 1; ++i) es.emplace_back(olo + 1, olo + 1 + i);

    return {n, es};
}

pair<int, vector<pii>> solution(const int x, const int y) {
    const auto n = isqrt(x + y);
    if (!n) return {0, {}};

    const auto olo = odd_levels_occupancy(y, *n);
    if (!olo) return {0, {}};

    return construct_tree(*n, *olo);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int x, y;
        cin >> x >> y;

        const auto [n, es] = solution(x, y);
        if (n) {
            cout << "YES" << '\n' << n << '\n';

            for (const auto [u, v] : es) {
                cout << u << ' ' << v << '\n';
            }
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
