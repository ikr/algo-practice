#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

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

vi gather_unused(const int n, const vector<pii> &ab) {
    set<int> used;
    for (const auto [a, b] : ab) {
        used.insert(a);
        used.insert(b);
    }

    vi unused;
    unused.reserve(n - sz(used));

    for (int i = 1; i <= n; ++i) {
        if (used.count(i)) continue;
        unused.push_back(i);
    }

    return unused;
}

enum class Color { WHITE, GRAY, BLACK };

bool is_acyclic(const vvi &g) {
    vector<Color> state(sz(g), Color::WHITE);

    function<bool(int)> recur;
    recur = [&](const int u) -> bool {
        state[u] = Color::GRAY;

        for (const auto v : g[u]) {
            if (state[v] == Color::GRAY) return false;
            if (!recur(v)) return false;
        }

        state[u] = Color::BLACK;
        return true;
    };

    for (int u = 0; u < sz(g); ++u) {
        if (state[u] == Color::WHITE) {
            if (!recur(u)) return false;
        }
    }

    return true;
}

vi min_proper_perm(const int n, const vector<pii> &ab) {
    vvi g(n + 1);

    for (const auto [a, b] : ab) {
        g[b].push_back(a);
    }

    vi ans;
    ans.reserve(n);
    for (int i = 1; i <= n; ++i) {
        ans.push_back(i);
    }

    return is_acyclic(g) ? ans : vi{};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<pii> ab(m);
    for (auto &[a, b] : ab) cin >> a >> b;

    const auto ans = min_proper_perm(n, ab);
    if (ans.empty()) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }
    return 0;
}
