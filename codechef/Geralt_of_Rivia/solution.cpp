#include <bits/stdc++.h>
using namespace std;
using Graph = unordered_multimap<int, int>;

int max_coins(const int n, const int s, Graph &g) {
    vector<bool> discovered(n, false);
    int ans = 0;
    function<void(int)> recur;

    recur = [&](const int u) {
        discovered[u] = true;
        ans += g.count(u);

        while (g.count(u)) {
            const auto it = g.equal_range(u).first;
            const int v = it->second;
            g.erase(it);
            if (!discovered[v]) recur(v);
        }
    };

    recur(s);
    return ans;
}

unordered_map<string, int> build_index(vector<string> cities) {
    const int n = cities.size();
    sort(begin(cities), end(cities));
    unordered_map<string, int> ans;
    for (int i = 0; i < n; ++i) ans[cities[i]] = i;
    return ans;
}

vector<string> unique_cities(const vector<pair<string, string>> &edges,
                             const string &origin) {
    unordered_set<string> uq{origin};
    for (const auto &[c1, c2] : edges) {
        uq.insert(c1);
        uq.insert(c2);
    }
    return vector<string>(cbegin(uq), cend(uq));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string c;
        cin >> c;

        vector<pair<string, string>> edges;
        for (int i = 0; i < n; ++i) {
            string a, b;
            cin >> a >> b;
            edges.emplace_back(a, b);
        }
        sort(begin(edges), end(edges));

        const auto cities = unique_cities(edges, c);
        const auto idx = build_index(cities);

        Graph g;
        for (const auto &[a, b] : edges) g.emplace(idx.at(a), idx.at(b));
        cout << max_coins(cities.size(), idx.at(c), g) << '\n';
    }

    return 0;
}
