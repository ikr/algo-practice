#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
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

vector<pii> increment_all_second(vector<pii> ps) {
    for (auto &[a, b] : ps) {
        if (b >= 0) ++b;
    }

    return ps;
}

int closest_special(const vi &fs, const vector<pii> &dsp) {
    int ans = -1;
    int d = 1e9;

    for (const auto f : fs) {
        assert(dsp[f].first >= 0);

        if (dsp[f].first < d) {
            d = dsp[f].first;
            ans = f;
        }
    }

    assert(ans >= 0);
    return ans;
}

vi distances_from(const vvi &g, const int f0) {
    vector<bool> discovered(sz(g), false);
    vi ans(sz(g));

    function<void(int, int)> dfs;
    dfs = [&](const int d, const int u) {
        discovered[u] = true;
        ans[u] = d;

        for (const auto v : g[u]) {
            if (discovered[v]) continue;
            dfs(d + 1, v);
        }
    };

    dfs(0, f0);
    return ans;
}

vi closest_specials(const vvi &g, const vi &fs) {
    vi ans(sz(g), -1);
    queue<pii> q;

    for (const auto f : fs) {
        q.emplace(f, f);
    }

    while (!q.empty()) {
        const auto [origin, u] = q.front();
        q.pop();

        ans[u] = origin;

        for (const int v : g[u]) {
            if (ans[v] != -1) continue;
            q.emplace(origin, v);
        }
    }

    return ans;
}

pair<vi, vi> diffs_and_specials(const vvi &g, const vi &fs, const int a) {
    const int n = sz(g);
    const set<int> fss(cbegin(fs), cend(fs));

    vector<pii> dsp(n, {-1, -1});
    vector<bool> discovered(n, false);

    function<void(int, int, int)> dfs;
    dfs = [&](const int d, const int f, const int u) {
        discovered[u] = true;
        const int special = fss.count(u) ? u : f;
        dsp[u] = {d, special};

        for (const auto v : g[u]) {
            if (discovered[v]) continue;
            dfs(d + 1, special, v);
        }
    };

    dfs(0, -1, a);

    const int f0 = closest_special(fs, dsp);
    const auto df0 = distances_from(g, f0);
    const auto css = closest_specials(g, fs);
    cerr << "css: " << css << endl;

    vi diffs(n);
    vi specials(n);

    for (int i = 0; i < n; ++i) {
        const auto [da, f] = dsp[i];

        if (f >= 0) {
            diffs[i] = da - dsp[f].first;
            specials[i] = f;
        } else {
            const int homes = -da;
            const int own = da;

            if (homes >= own) {
                diffs[i] = homes;
                specials[i] = f0;
            } else {
                diffs[i] = own;
                specials[i] = css[i];
            }
        }
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
