#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

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

vvi rooted_tree(const vvi &g, const int a) {
    vvi ans(sz(g));
    vector<bool> discovered(sz(g), false);

    function<void(int)> dfs;
    dfs = [&](const int u) {
        discovered[u] = true;
        for (const int v : g[u]) {
            if (discovered[v]) continue;
            ans[u].push_back(v);
            dfs(v);
        }
    };

    dfs(a);
    return ans;
}

vector<bool> subtree_specialness_indicators(const vvi &t, const set<int> &fs,
                                            const int a) {
    const int n = sz(t);
    vi memo(n, -1);

    function<int(int)> recur;
    recur = [&](const int u) -> int {
        if (memo[u] != -1) return memo[u];

        int ans = fs.count(u) ? 1 : 0;

        for (const int v : t[u]) {
            const int sub = recur(v);
            if (!ans && sub == 1) ans = 1;
        }

        memo[u] = ans;
        return ans;
    };

    recur(a);

    vector<bool> ans(n);
    transform(cbegin(memo), cend(memo), begin(ans),
              [](const int x) { return x == 1; });
    return ans;
}

pair<vi, vi> diffs_and_specials(const vvi &g, const vi &fs, const int a) {
    const int n = sz(g);
    const auto t = rooted_tree(g, a);

    cerr << "ind: "
         << subtree_specialness_indicators(t, set<int>(cbegin(fs), cend(fs)), a)
         << endl;

    vi diffs(n);
    vi specials(n);

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
