#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

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

vi largest_group(atcoder::dsu &cs) {
    const auto gs = cs.groups();
    return *max_element(cbegin(gs), cend(gs), [](const vi &lhs, const vi &rhs) {
        return sz(lhs) < sz(rhs);
    });
}

set<int> xs_excluding_ys(const vi &xs, const vi &ys) {
    set<int> ans(cbegin(xs), cbegin(xs));
    for (const auto y : ys) ans.erase(y);
    return ans;
}

ll min_cost_to_connect_all(const vi &vs, const vector<pii> &es) {
    atcoder::dsu cs;
    for (const auto [u, v] : es) cs.merge(u, v);

    auto internals = largest_group(cs);
    auto externals = xs_excluding_ys(vs, internals);
    ll ans = 0;

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
