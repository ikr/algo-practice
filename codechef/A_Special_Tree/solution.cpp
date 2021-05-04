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

pair<vi, vi> diffs_and_specials(const vvi &g, const vi &fs, const int a) {
    const int n = sz(g);
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
