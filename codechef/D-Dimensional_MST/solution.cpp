#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using pi = pair<int, int>;
using vpi = vector<pi>;
using ll = long long;

namespace atcoder {
struct dsu final {
    dsu() : _n(0) {}
    dsu(int n) : _n(n), parent_or_size(n, -1) {}

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
                               [&](const vi &v) { return v.empty(); }),
                     result.end());
        return result;
    }

  private:
    int _n;
    vi parent_or_size;
};
} // namespace atcoder

enum class Dir { FWD, BWD };

template <typename T> struct mmax {
    constexpr T operator()(const T &a, const T &b) const {
        return std::max(a, b);
    }
};

template <typename Iter, typename R, typename Binop1, typename Binop2>
R ttransform_reduce(Iter first1, Iter last1, Iter first2, R init, Binop1 binop1,
                    Binop2 binop2) {
    R ans = init;

    for (auto it = first1, jt = first2; it != last1; ++it, ++jt) {
        ans = binop1(ans, binop2(*it, *jt));
    }

    return ans;
}

vi rotate45(const vi &xs) {
    const int sz = xs.size();
    if (sz == 1) return xs;
    if (sz == 2) return {xs[0] + xs[1], xs[1] - xs[0]};

    if (sz == 3)
        return {xs[0] + xs[1] + xs[2], xs[0] + xs[1] - xs[2],
                xs[0] - xs[1] + xs[2], xs[0] - xs[1] - xs[2]};

    if (sz == 4)
        return {xs[0] + xs[1] + xs[2] + xs[3], xs[0] - xs[1] + xs[2] + xs[3],
                xs[0] + xs[1] - xs[2] + xs[3], xs[0] + xs[1] + xs[2] - xs[3],
                xs[0] - xs[1] - xs[2] + xs[3], xs[0] + xs[1] - xs[2] - xs[3],
                xs[0] - xs[1] + xs[2] - xs[3], xs[0] - xs[1] - xs[2] - xs[3]};

    if (sz == 5)
        return {xs[0] + xs[1] + xs[2] + xs[3] + xs[4],
                xs[0] - xs[1] + xs[2] + xs[3] + xs[4],
                xs[0] + xs[1] - xs[2] + xs[3] + xs[4],
                xs[0] + xs[1] + xs[2] - xs[3] + xs[4],
                xs[0] + xs[1] + xs[2] + xs[3] - xs[4],

                xs[0] - xs[1] - xs[2] + xs[3] + xs[4],
                xs[0] - xs[1] + xs[2] - xs[3] + xs[4],
                xs[0] - xs[1] + xs[2] + xs[3] - xs[4],
                xs[0] + xs[1] - xs[2] - xs[3] + xs[4],
                xs[0] + xs[1] - xs[2] + xs[3] - xs[4],
                xs[0] + xs[1] + xs[2] - xs[3] - xs[4],

                xs[0] - xs[1] - xs[2] - xs[3] + xs[4],
                xs[0] - xs[1] - xs[2] + xs[3] - xs[4],
                xs[0] + xs[1] - xs[2] - xs[3] - xs[4],

                xs[0] - xs[1] - xs[2] - xs[3] - xs[4]};

    assert(false && "Higher dimensions not supported");
    return xs;
}

vvi rotate45_(const vvi &xss) {
    vvi ans(xss.size());
    transform(cbegin(xss), cend(xss), begin(ans), rotate45);
    return ans;
}

int manh(const int x, const int y) { return abs(x - y); }

int manh_(const vi &xs, const vi &ys) {
    return ttransform_reduce(cbegin(xs), cend(xs), cbegin(ys), 0, plus<int>{},
                             manh);
}

int cheb(const vi &xs, const vi &ys) {
    return ttransform_reduce(cbegin(xs), cend(xs), cbegin(ys), -1, mmax<int>{},
                             manh);
}

void test_rotation(const vvi &xss) {
    const int n = xss.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            cout << manh_(xss[i], xss[j]) << ' ';
        }
    }
    cout << '\n';

    const auto yss = rotate45_(xss);
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            cout << cheb(yss[i], yss[j]) << ' ';
        }
    }
    cout << '\n';
}

int bruteforce(vvi xss) {
    vvi yss{xss.back()};
    yss.reserve(xss.size());
    xss.pop_back();
    if (xss.empty()) return 0;
    int ans = 0;

    do {
        int best_d = -1;
        auto best_it = xss.cend();

        for (auto jt = cbegin(yss); jt != cend(yss); ++jt) {
            for (auto it = cbegin(xss); it != cend(xss); ++it) {
                const int d = manh_(*jt, *it);
                if (d > best_d) {
                    best_d = d;
                    best_it = it;
                }
            }
        }

        ans += best_d;
        yss.push_back(*best_it);
        xss.erase(best_it);
    } while (!xss.empty());

    return ans;
}

vector<vpi> gather_indices_by_coord(const vvi &xss) {
    const int n = xss.size();
    const int d = xss[0].size();

    vector<vpi> ans(d, vpi(n));
    for (int j = 0; j < d; ++j) {
        for (int i = 0; i < n; ++i) ans[j][i] = pi{xss[i][j], i};
        sort(begin(ans[j]), end(ans[j]));
    }
    return ans;
}

ll mst_cheb_weight(const vvi &xss) {
    const int n = xss.size();
    if (n == 1) return 0;
    const int d = xss[0].size();

    const auto indices_by_coord = gather_indices_by_coord(xss);
    vpi spans(d, pi{0, n - 1});
    atcoder::dsu g(n);
    ll ans = 0;

    for (;;) {
        int best_w = -1;
        int best_k = -1;
        Dir best_dir = Dir::FWD;

        for (int k = 0; k < d; ++k) {
            const auto [fwd, bwd] = spans[k];

            if (fwd < n - 1) {
                const int fwd_w = indices_by_coord[k][n - 1].first -
                                  indices_by_coord[k][fwd].first;

                if (fwd_w > best_w) {
                    best_w = fwd_w;
                    best_k = k;
                    best_dir = Dir::FWD;
                }
            }

            if (bwd > 0) {
                const int bwd_w = indices_by_coord[k][bwd].first -
                                  indices_by_coord[k][0].first;

                if (bwd_w > best_w) {
                    best_w = bwd_w;
                    best_k = k;
                    best_dir = Dir::BWD;
                }
            }
        }

        if (best_w == -1) break;

        if (best_dir == Dir::FWD) {
            const int x = indices_by_coord[best_k][spans[best_k].first].second;
            const int y = indices_by_coord[best_k][n - 1].second;

            if (!g.same(x, y)) {
                ans += best_w;
                g.merge(x, y);
            }

            ++spans[best_k].first;
        } else {
            const int x = indices_by_coord[best_k][0].second;
            const int y = indices_by_coord[best_k][spans[best_k].second].second;

            if (!g.same(x, y)) {
                ans += best_w;
                g.merge(x, y);
            }

            --spans[best_k].second;
        }
    }

    assert(g.size(0) == n);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, D;
    cin >> N >> D;

    vvi xss(N, vi(D, 0));
    for (auto &xs : xss) {
        for (auto &x : xs) cin >> x;
    }

    test_rotation(xss);
    cout << bruteforce(xss) << '\n';
    cout << mst_cheb_weight(rotate45_(xss)) << '\n';

    return 0;
}
