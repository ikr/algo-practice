#include <atcoder/lazysegtree>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Query final {
    int reachable_from;
    int without_visiting;
    ll value;
};

vector<ll> final_vertex_values(vector<pair<int, int>> edges,
                               vector<Query> queries) {}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pair<int, int>> edges(n);
    for (auto &[a, b] : edges) {
        cin >> a >> b;
        --a;
        --b;
    }

    int q;
    cin >> q;

    vector<Query> queries(q);
    for (auto &[reachable_from, without_visiting, value] : queries) {
        int t, e;
        cin >> t >> e >> value;

        reachable_from = t == 1 ? edges[e].first : edges[e].second;
        without_visiting = t == 1 ? edges[e].second : edges[e].first;
    }

    const auto ans = final_vertex_values(move(edges), move(queries));
    for (const ll v : ans) cout << v << '\n';
    return 0;
}
