#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll min_moves(const vi &xs) {
    if (sz(xs) == 2) return 0;
    if (sz(xs) == 3) return min(xs[1] - xs[0], xs[2] - xs[1]);

    const auto moves_num = [&](const pii ab, const pii cd) -> ll {
        const auto [a, b] = ab;
        const auto [c, d] = cd;

        assert(a <= b);
        assert(c <= d);

        return abs(llof(b) - llof(a) - llof(c - d));
    };

    const int a = xs[0];
    const int b = xs[1];
    const int rl = xs[2];

    const int c = xs[sz(xs) - 2];
    const int d = xs.back();
    const int rr = xs[sz(xs) - 3];

    return min({moves_num({a, c}, {b, d}), moves_num({a, d}, {b, c}),
                moves_num({a, b}, {rl, d}), moves_num({a, rr}, {c, d})});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        cout << min_moves(xs) << '\n';
    }

    return 0;
}
