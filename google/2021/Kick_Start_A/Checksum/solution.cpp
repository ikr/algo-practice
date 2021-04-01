#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

namespace atcoder {
// Implement (union by size) + (path compression)
// Reference:
// Zvi Galil and Giuseppe F. Italiano,
// Data structures and algorithms for disjoint set union problems
struct dsu final {
    dsu() : _n(0) {}
    explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    vvi groups() {
        vi leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vvi result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(remove_if(result.begin(), result.end(),
                               [&](const vector<int> &v) { return v.empty(); }),
                     result.end());
        return result;
    }

  private:
    int _n;
    // root node: -1 * component size
    // otherwise: parent
    vi parent_or_size;
};
} // namespace atcoder

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pii> gather_edges(const vvi &src) {
    vector<pii> ans;

    for (int ro = 0; ro < sz(src); ++ro) {
        for (int co = 0; co < sz(src[0]); ++co) {
            if (src[ro][co] == -1) ans.emplace_back(ro, co);
        }
    }

    return ans;
}

void sort_edges(const vvi &costs, vector<pii> &edges) {
    sort(begin(edges), end(edges), [&costs](const pii lhs, const pii rhs) {
        return costs[lhs.first][lhs.second] < costs[rhs.first][rhs.second];
    });
}

int mst_weight(const int n, const vvi &costs, const vector<pii> &edges) {
    atcoder::dsu cs(2 * n);
    int ans = 0;

    for (const auto [ro, co] : edges) {
        if (!ans || !cs.same(ro, n + co)) {
            cs.merge(ro, n + co);
            ans += costs[ro][co];
        }
    }

    return ans;
}

int total_weight(const vvi &costs, const vector<pii> &edges) {
    return accumulate(cbegin(edges), cend(edges), 0,
                      [&costs](const int memo, const pii x) {
                          return memo + costs[x.first][x.second];
                      });
}

int solve(const vvi &src, const vvi &costs) {
    auto edges = gather_edges(src);
    sort_edges(costs, edges);
    return total_weight(costs, edges) - mst_weight(sz(src), costs, edges);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;

        vvi src(n, vi(n, 0));
        for (auto &line : src) {
            for (auto &cell : line) cin >> cell;
        }

        vvi costs(n, vi(n, 0));
        for (auto &line : costs) {
            for (auto &cell : line) cin >> cell;
        }

        vi rs(n, 0);
        for (auto &c : rs) cin >> c;

        vi cs(n, 0);
        for (auto &c : cs) cin >> c;

        cout << "Case #" << i << ": " << solve(src, costs) << '\n';
    }

    return 0;
}
