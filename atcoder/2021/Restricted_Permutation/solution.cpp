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

vvi graph(const int n, const vector<pii> &ab) {
    vvi g(n);
    for (const auto [a, b] : ab) {
        g[a].push_back(b);
    }
    return g;
}

vvi inverted_graph(const vvi &g) {
    vvi ans(sz(g));
    for (int u = 0; u < sz(g); ++u) {
        for (const auto v : g[u]) {
            ans[v].push_back(u);
        }
    }
    return ans;
}

vi sources(const vvi &g) {
    const auto g_ = inverted_graph(g);
    vi ans;

    for (int u = 0; u < sz(g_); ++u) {
        if (g_[u].empty()) {
            ans.push_back(u);
        }
    }

    return ans;
}

vi toposort_with_a_twist(const vvi &g) {
    const auto n = sz(g);
    vector<bool> visited(n, false);

    vi ans;
    ans.reserve(n);

    function<void(int)> recur;
    recur = [&](const int u) {
        for (const auto v : g[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            recur(v);
        }
        ans.push_back(u);
    };

    for (const auto u : sources(g)) {
        recur(u);
    }

    reverse(begin(ans), end(ans));
    return ans;
}

vi min_proper_perm(const int n, const vector<pii> &ab) {
    const auto g = graph(n, ab);
    return is_acyclic(g) ? toposort_with_a_twist(g) : vi{};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<pii> ab(m);
    for (auto &[a, b] : ab) {
        cin >> a >> b;
        --a;
        --b;
    }

    const auto ans = min_proper_perm(n, ab);
    if (ans.empty()) {
        cout << "-1\n";
    } else {
        for (auto it = cbegin(ans); it != cend(ans); ++it) {
            if (it != cbegin(ans)) cout << ' ';
            cout << ((*it) + 1);
        }

        cout << '\n';
    }
    return 0;
}
