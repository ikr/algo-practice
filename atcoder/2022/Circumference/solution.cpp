#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

constexpr ll square(const ll x) { return x * x; };

bool is_p_inside_a(const tll a, const pll p) {
    const auto [x, y] = p;
    const auto [x0, y0, r] = a;
    return square(x - x0) + square(y - y0) < square(r);
}

bool is_a_inside_b(const tll a, const tll b) {
    const auto [xa, ya, ra] = a;
    const auto [xb, yb, rb] = b;
    if (!is_p_inside_a(b, {xa, ya})) return false;

    const auto d = sqrt(doof(square(xa - xb) + square(ya - yb)));
    return d + doof(ra) < doof(rb);
}

bool circles_touch(const tll a, const tll b) {
    if (a == b) return true;
    if (is_a_inside_b(a, b) || is_a_inside_b(b, a)) return false;

    const auto [xa, ya, ra] = a;
    const auto [xb, yb, rb] = b;
    const auto d2 = square(xa - xb) + square(ya - yb);

    return square(ra + rb) <= d2;
}

int index_of(const vector<tll> &cs, const pll a) {
    for (int i = 0; i < sz(cs); ++i) {
        const auto [x, y] = a;
        const auto [x0, y0, r] = cs[i];
        if (square(x - x0) + square(y - y0) == r * r) {
            return i;
        }
    }

    assert(false && "index_of");
    return -1;
}

bool is_possible(const vector<tll> &cs, const pll s, const pll t) {
    const auto is = index_of(cs, s);
    const auto it = index_of(cs, t);

    atcoder::dsu tr(sz(cs));

    for (int u = 0; u < sz(cs) - 1; ++u) {
        for (int v = u + 1; v < sz(cs); ++v) {
            if (circles_touch(cs[u], cs[v])) {
                tr.merge(u, v);
            }
        }
    }

    return tr.same(is, it);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    pll s, t;
    cin >> s.first >> s.second >> t.first >> t.second;

    vector<tll> cs(N);
    for (auto &[x, y, r] : cs) {
        cin >> x >> y >> r;
    }

    cout << (is_possible(cs, s, t) ? "Yes" : "No") << '\n';
    return 0;
}
