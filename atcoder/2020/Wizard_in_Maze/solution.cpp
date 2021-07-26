#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> &lhs, const pair<T, T> &rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

bool in_bounds(const int H, const int W, const pi x) {
    const auto [ro, co] = x;
    return 0 <= ro && ro < H && 0 <= co && co < W;
}

vector<vector<int>> mark_components(const vector<string> &rows) {
    const int H = rows.size();
    const int W = rows[0].size();

    vector<vector<int>> ans(H, vector<int>(W, -1));
    function<void(pi)> dfs;
    int curr = -1;

    dfs = [&dfs, &rows, &H, &W, &ans, &curr](const pi u) {
        const auto [ro, co] = u;
        ans[ro][co] = curr;

        for (const auto d : vector<pi>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
            const auto v = u + d;
            if (!in_bounds(H, W, v) || rows[v.first][v.second] == '#' ||
                ans[v.first][v.second] != -1)
                continue;
            dfs(v);
        }
    };

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (rows[ro][co] == '#' || ans[ro][co] != -1) continue;
            ++curr;
            dfs({ro, co});
        }
    }

    return ans;
}

unordered_map<int, unordered_set<int>>
build_componenets_graph(const vector<vector<int>> &comp) {
    const int H = comp.size();
    const int W = comp[0].size();
    unordered_map<int, unordered_set<int>> ans;
    const set<pi> adj{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (comp[ro][co] == -1) continue;

            for (int dro = -2; dro <= 2; ++dro) {
                for (int dco = -2; dco <= 2; ++dco) {
                    if (!in_bounds(H, W, {ro + dro, co + dco}) ||
                        comp[ro + dro][co + dco] == -1 ||
                        comp[ro][co] == comp[ro + dro][co + dco])
                        continue;

                    const pi d{dro, dco};
                    if (adj.count(d)) continue;

                    ans[comp[ro][co]].insert(comp[ro + dro][co + dco]);
                    ans[comp[ro + dro][co + dco]].insert(comp[ro][co]);
                }
            }
        }
    }

    return ans;
}

vector<pi> gather_starters(const vector<string> &rows, const pi s) {
    const int H = rows.size();
    const int W = rows[0].size();
    const auto [ro, co] = s;
    if (rows[ro][co] == '.') return {s};

    const set<pi> adj{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<pi> ans;

    for (int dro = -2; dro <= 2; ++dro) {
        for (int dco = -2; dco <= 2; ++dco) {
            if (!in_bounds(H, W, {ro + dro, co + dco}) ||
                rows[ro + dro][co + dco] == '#')
                continue;

            const pi d{dro, dco};
            if (adj.count(d)) continue;

            ans.push_back(s + d);
        }
    }

    return ans;
}

int min_warps(const vector<string> &rows, const pi s, const pi t) {
    const auto comp = mark_components(rows);
    const auto g = build_componenets_graph(comp);
    const auto starters = gather_starters(rows, s);

    vector<int> starter_components;
    transform(starters.cbegin(), starters.cend(),
              back_inserter(starter_components),
              [&comp](const pi x) { return comp[x.first][x.second]; });

    sort(starter_components.begin(), starter_components.end());
    starter_components.erase(
        unique(starter_components.begin(), starter_components.end()),
        starter_components.end());

    const int tcomp = comp[t.first][t.second];
    unordered_map<int, int> ans;

    queue<int> q;
    for (const auto c : starter_components) {
        const int initial_warps = rows[s.first][s.second] == '#' ? 1 : 0;
        if (c == tcomp) return initial_warps;
        ans[c] = initial_warps;
        q.push(c);
    }

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();
        assert(ans.count(u));

        if (!g.count(u)) continue;
        const auto &vs = g.at(u);
        for (const auto v : vs) {
            if (ans.count(v)) continue;
            ans[v] = ans[u] + 1;
            q.push(v);
        }
    }

    return ans.count(tcomp) ? ans[tcomp] : -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int H, W;
    cin >> H >> W;

    pi s;
    cin >> s.first >> s.second;
    --s.first;
    --s.second;

    pi t;
    cin >> t.first >> t.second;
    --t.first;
    --t.second;

    vector<string> rows(H, string(W, ' '));
    for (auto &r : rows) cin >> r;

    cout << min_warps(rows, s, t) << '\n';

    return 0;
}
