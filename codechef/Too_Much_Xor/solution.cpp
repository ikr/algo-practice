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
    map<int, array<int, 2>> f;

    int hi = -1;
    for (int i = 0; i < sz(a); ++i) {
        if (!f.count(a[i])) {
            f[a[i]] = {0, 0};
        }

        ++f[a[i]][i % 2];
        if (f[a[i]][i % 2] > 1) {
            hi = i;
            break;
        }
    }

    if (hi == -1) return nullopt;

    for (int i = 0; i < hi; ++i) {
        if ((i % 2) != (hi % 2)) continue;
        if (a[i] == a[hi]) return pii{i, hi};
    }

    assert(false);
    return nullopt;
}

int other_index(const int n, const int p, const int q) {
    assert(n > 2);
    for (int i = 0; i < n; ++i) {
        if (i == p || i == q || (i % 2) == (p % 2)) continue;
        return i;
    }

    assert(false);
    return -1;
}

optional<vector<Tri>> solve(const vi &a) {
    if (sz(a) == 1) return vector<Tri>{};

    if (sz(a) == 2) {
        if ((a[0] ^ a[1]) > 0) return vector<Tri>{};
        return nullopt;
    }

    const auto pq = driving_indices(a);
    if (!pq) return nullopt;

    const auto [p, q] = *pq;
    assert((p % 2) == (q % 2));

    const auto z = other_index(sz(a), p, q);
    vector<Tri> ans;
    ans.emplace_back(p, q, z);

    for (int i = 0; i < sz(a); ++i) {
        if (i == p || i == q || i == z) continue;

        if ((i % 2) == (z % 2)) {
            ans.emplace_back(p, q, i);
        } else {
            assert((i % 2) == (p % 2));
            ans.emplace_back(p, z, i);
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

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
