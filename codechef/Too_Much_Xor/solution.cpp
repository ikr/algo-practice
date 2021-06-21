#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Tri = tuple<int, int, int>;

optional<pii> driving_indices(const vi &a) {
    for (int i = 2; i < sz(a); i += 2) {
        if (a[i] != a[0]) return pii{0, i};
    }

    for (int i = 3; i < sz(a); i += 2) {
        if (a[i] != a[1]) return pii{1, i};
    }

    return nullopt;
}

pii opposing_indices(const int n, const int p, const int q) {
    assert(n > 3);

    vi ans;

    for (int i = 0; i < n; ++i) {
        if (i == p || i == q || i % 2 == p % 2) continue;

        ans.push_back(i);
        if (sz(ans) == 2) break;
    }

    assert(sz(ans) == 2);
    return {ans[0], ans[1]};
}

optional<int> single_repeated(const vi &a) {
    assert(!a.empty());

    if (all_of(next(cbegin(a)), cend(a),
               [&a](const int y) { return y == a[0]; })) {
        return a[0];
    }

    return nullopt;
}

vector<Tri> grid_ops(const int n) {
    vector<Tri> ans;

    for (int i = 1; i < n; i += 2) {
        ans.emplace_back(0, 2, i);
    }

    return ans;
}

optional<vector<Tri>> solve(const vi &a) {
    if (sz(a) == 1) return vector<Tri>{};

    const auto s = single_repeated(a);
    if (s && *s == 0) return nullopt;

    if (sz(a) == 2) {
        if (a[0] == a[1]) return nullopt;
        return vector<Tri>{};
    }

    if (sz(a) == 3) {
        if (a[1] == 0) {
            if (a[0] != 0) return vector<Tri>{{0, 1, 2}};
            if (a[2] != 0) return vector<Tri>{{1, 2, 0}};

            assert(false && "Ether 0th or 2nd must be non-zero");
            return nullopt;
        }

        if (a[0] == a[2] && a[0] != 0) return vector<Tri>{{0, 2, 1}};

        return nullopt;
    }

    if (s) return grid_ops(sz(a));

    const auto pq = driving_indices(a);
    if (!pq) return grid_ops(sz(a));

    const auto [p, q] = *pq;
    assert(p % 2 == q % 2);

    vector<Tri> ans;

    for (int i = 0; i < sz(a); ++i) {
        if (i % 2 == p % 2) continue;
        ans.emplace_back(p, q, i);
    }

    const auto [y, z] = opposing_indices(sz(a), p, q);
    assert(y % 2 == z % 2);

    for (int i = 0; i < sz(a); ++i) {
        if (i % 2 == y % 2) continue;
        ans.emplace_back(y, z, i);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi a(n);
        for (auto &x : a) cin >> x;

        const auto ans = solve(a);
        if (ans) {
            cout << sz(*ans) << '\n';
            for (const auto [i, j, k] : *ans) {
                cout << i + 1 << ' ' << j + 1 << ' ' << k + 1 << '\n';
            }
        } else {
            cout << -1 << '\n';
        }
    }

    return 0;
}
