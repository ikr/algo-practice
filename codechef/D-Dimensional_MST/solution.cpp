#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using Iter = multimap<int, int>::const_iterator;
constexpr static int INF = 1e9;

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

    vector<vector<int>> groups() {
        vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(_n);
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
    vector<int> parent_or_size;
};
} // namespace atcoder

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
    const int s = accumulate(cbegin(xs), cend(xs), 0);

    vi ans(sz + 1, s);
    for (int i = 1; i <= sz; ++i) ans[i] -= 2 * xs[i - 1];
    return ans;
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
    return ttransform_reduce(cbegin(xs), cend(xs), cbegin(ys), -INF,
                             mmax<int>{}, manh);
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

vector<multimap<int, int>> gather_indices_by_coord(const vvi &xss) {
    const int n = xss.size();
    const int d = xss[0].size();

    vector<multimap<int, int>> ans(d);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d; ++j) {
            ans[j].emplace(xss[i][j], i);
        }
    }
    return ans;
}

vector<pair<Iter, Iter>> gather_cursors(const vector<multimap<int, int>> &vmm) {
    vector<pair<Iter, Iter>> ans;
    transform(cbegin(vmm), cend(vmm), back_inserter(ans), [](const auto &mm) {
        return pair<Iter, Iter>{cbegin(mm), prev(cend(mm))};
    });
    return ans;
}

void advance(pair<Iter, Iter> &itjt) {
    auto &[it, jt] = itjt;
    assert(it != jt);

    const auto x = it->first;
    const auto xx = next(it)->first;
    const auto yy = prev(jt)->first;
    const auto y = jt->first;

    if (abs(xx - y) > abs(x - yy)) {
        ++it;
    } else {
        --jt;
    }
}

int mst_cheb_weight(const vvi &xss) {
    const int n = xss.size();
    if (n == 1) return 0;
    const int d = xss[0].size();

    const auto indices_by_coord = gather_indices_by_coord(xss);
    auto cursors = gather_cursors(indices_by_coord);
    atcoder::dsu g(n);
    int ans = 0;

    for (;;) {
        int best_w = -1;
        int best_k = -1;

        for (int k = 0; k < d; ++k) {
            auto &[it, jt] = cursors[k];
            if (it == jt) continue;

            const int w = abs(it->first - jt->first);

            if (w > best_w) {
                best_w = w;
                best_k = k;
            }
        }

        if (best_w == -1) break;
        auto &[it, jt] = cursors[best_k];
        if (!g.same(it->second, jt->second)) {
            ans += abs(it->first - jt->first);
            g.merge(it->second, jt->second);
        }
        advance(cursors[best_k]);
    }

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

    // test_rotation(xss);
    cout << bruteforce(xss) << '\n';
    cout << mst_cheb_weight(rotate45_(xss)) << '\n';

    return 0;
}
