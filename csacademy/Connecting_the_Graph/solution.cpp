#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

namespace atcoder {
// Implement (union by size) + (path compression)
// Reference:
// Zvi Galil and Giuseppe F. Italiano,
// Data structures and algorithms for disjoint set union problems
struct dsu {
  public:
    dsu() : _n(0) {}
    explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
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

    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(std::remove_if(
                         result.begin(), result.end(),
                         [&](const std::vector<int> &v) { return v.empty(); }),
                     result.end());
        return result;
    }

  private:
    int _n;
    // root node: -1 * component size
    // otherwise: parent
    std::vector<int> parent_or_size;
};

} // namespace atcoder

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pii> closest_value_indices(const vi &xs) {
    vi idx(sz(xs));
    iota(begin(idx), end(idx), 0);
    sort(begin(idx), end(idx),
         [&xs](const int i, const int j) { return xs[i] < xs[j]; });

    vector<pii> ans;
    ans.reserve(sz(xs) - 1);

    for (int i = 1; i < sz(idx); ++i) {
        ans.emplace_back(idx[i - 1], idx[i]);
    }

    sort(begin(ans), end(ans), [&xs](const pii uv, const pii pq) {
        const auto [u, v] = uv;
        const auto [p, q] = pq;
        return abs(u - v) < abs(p - q);
    });

    return ans;
}

constexpr ll square(const ll x) { return x * x; }

ll min_cost_to_connect_all(const vi &vs, const vector<pii> &es) {
    atcoder::dsu cs(sz(vs));
    for (const auto [u, v] : es) {
        cs.merge(u, v);
    }

    const auto roads = closest_value_indices(vs);
    ll ans = 0;

    for (const auto [i, j] : roads) {
        if (!cs.same(i, j)) {
            cs.merge(i, j);
            ans += square(vs[i] - vs[j]);
        }

        if (cs.size(i) == sz(vs)) break;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vi vs(n);
    for (auto &v : vs) cin >> v;

    vector<pii> es(m);
    for (auto &[u, v] : es) {
        cin >> u >> v;
        --u;
        --v;
    }

    cout << min_cost_to_connect_all(vs, es) << '\n';
    return 0;
}
