#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

static constexpr int N_MAX = 20;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi toposort(const vvi &g, const vi &vs) {
    assert(!empty(vs));
    vi ans;
    vector<bool> discovered(N_MAX, false);

    function<void(int)> dfs;
    dfs = [&](const int u) {
        ans.push_back(u);
        discovered[u] = true;

        for (const int v : g[u]) {
            if (discovered[v]) continue;
            dfs(v);
        }
    };

    dfs(vs[0]);
    assert(sz(ans) == sz(vs));
    return ans;
}

bool is_valid(const vector<vector<bool>> &es, const vi &vs,
              const vi &coloring) {
    assert(sz(coloring) == sz(vs));

    for (int i = 0; i < sz(vs) - 1; ++i) {
        for (int j = i + 1; j < sz(vs); ++j) {
            if (coloring[i] == coloring[j] && es[vs[i]][vs[j]]) {
                return false;
            }
        }
    }

    return true;
}

int component_rgb_colorings_num(const vector<vector<bool>> &es, const vi &vs) {
    int ans = 0;

    for (int head = 0; head < 3; ++head) {
        vi coloring(sz(vs), -1);
        coloring[0] = head;

        for (int tail_bits = 0; tail_bits < (1 << (sz(vs) - 1)); ++tail_bits) {
            for (int i = 1; i < sz(vs); ++i) {
                const int i_bit = i - 1;

                vi possible_colors;

                for (int j = 0; j < i; ++j) {
                    if (es[vs[i]][vs[j]]) {
                        assert(coloring[j] != -1);

                        for (int color = 0; color < 3; ++color) {
                            if (color != coloring[j]) {
                                possible_colors.push_back(color);
                            }
                        }

                        break;
                    }
                }

                assert(sz(possible_colors) == 2);

                coloring[i] =
                    possible_colors[(tail_bits & (1 << i_bit)) ? 1 : 0];
            }

            if (is_valid(es, vs, coloring)) ++ans;
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vvi g(n);
    vector<vector<bool>> es(n, vector(n, false));
    atcoder::dsu comps(n);

    while (m--) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;

        g[a].push_back(b);
        g[b].push_back(a);

        es[a][b] = true;
        es[b][a] = true;

        comps.merge(a, b);
    }

    ll ans = 1;

    for (const auto vs : comps.groups()) {
        ans *= component_rgb_colorings_num(es, toposort(g, vs));
    }

    cout << ans << '\n';
    return 0;
}
