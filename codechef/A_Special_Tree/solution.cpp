#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int mlog2(const unsigned int x) {
    return inof(8U * sizeof(unsigned int) - __builtin_clz(x) - 1U);
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vi increment_all(vi xs) {
    for (auto &x : xs) ++x;
    return xs;
}

pair<vvi, vi> rooted_tree(const vvi &g, const int a) {
    vvi ans(sz(g));
    vi ps(sz(g), -1);
    vector<bool> discovered(sz(g), false);

    function<void(int)> dfs;
    dfs = [&](const int u) {
        discovered[u] = true;

        for (const int v : g[u]) {
            if (discovered[v]) continue;

            ans[u].push_back(v);
            ps[v] = u;
            dfs(v);
        }
    };

    dfs(a);
    return {ans, ps};
}

vi levels(const vvi &t, const int a) {
    vi ans(sz(t), -1);

    function<void(int, int)> recur;
    recur = [&](const int l, const int u) {
        ans[u] = l;
        for (const int v : t[u]) recur(l + 1, v);
    };

    recur(0, a);
    return ans;
}

vi subtree_specials(const vvi &t, const vi &ls, const set<int> &fs,
                    const int a) {
    vi ans(sz(t), -1);

    function<void(int)> recur;
    recur = [&](const int u) {
        for (const int v : t[u]) recur(v);

        if (fs.count(u)) {
            ans[u] = u;
        } else {
            priority_queue<pii> pq;

            for (const int v : t[u]) {
                if (ans[v] == -1) continue;
                pq.emplace(-ls[ans[v]], ans[v]);
            }

            if (!pq.empty()) {
                ans[u] = pq.top().second;
            }
        }
    };

    recur(a);
    return ans;
}

vvi lifts(const vi &ps) {
    const int n = sz(ps);
    vvi up(n, vi(mlog2(n) + 1, -1));

    for (int j = 0; j < mlog2(n) + 1; ++j) {
        for (int i = 0; i < n; ++i) {
            up[i][j] =
                j == 0 ? ps[i]
                       : (up[i][j - 1] == -1 ? -1 : up[up[i][j - 1]][j - 1]);
        }
    }

    return up;
}

int x_point_for(const vvi &up, const vi &sts, const int b) {
    if (sts[b] >= 0) return b;

    assert(!up.empty());
    int last_lift_tried = sz(up[0]);
    int curr = b;

    do {
        --last_lift_tried;
        const int anc = up[curr][last_lift_tried];
        if (anc != -1 && sts[anc] == -1) curr = anc;
    } while (last_lift_tried > 0);

    assert(up[curr][0] >= 0);
    return up[curr][0];
}

pair<vi, vi> diffs_and_specials(const vvi &g, const vi &fs, const int a) {
    const int n = sz(g);
    const auto [t, ps] = rooted_tree(g, a);
    const auto up = lifts(ps);
    const auto ls = levels(t, a);
    const auto sts = subtree_specials(t, ls, set<int>(cbegin(fs), cend(fs)), a);

    vi diffs(n);
    vi specials(n);

    for (int b = 0; b < n; ++b) {
        const auto x = x_point_for(up, sts, b);
        diffs[b] = ls[x] - ls[a] - (ls[b] - ls[x]);
        specials[b] = sts[x];
    }

    return {diffs, specials};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n, k, a;
        cin >> n >> k >> a;
        --a;

        vi fs(k);
        for (auto &f : fs) {
            cin >> f;
            --f;
        }

        vvi g(n);
        for (int i = 1; i <= n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;

            g[u].push_back(v);
            g[v].push_back(u);
        }

        auto [diffs, specials] = diffs_and_specials(g, fs, a);

        cout << diffs << '\n';
        cout << increment_all(specials) << '\n';
    }

    return 0;
}
