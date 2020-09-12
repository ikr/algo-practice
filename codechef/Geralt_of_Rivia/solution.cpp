#include <bits/stdc++.h>
using namespace std;
using Graph = unordered_multimap<int, int>;

int max_coins(const int n, const Graph &g) {
    vector<bool> parents(n, false);
    function<int(int)> recur;

    recur = [&](const int u) {
        parents[u] = true;

        int sub = -1;
        const auto [first, last] = g.equal_range(u);
        for (auto it = first; it != last; ++it) {
            const int v = it->second;
            if (parents[v]) continue;

            sub = recur(v);
        }

        parents[u] = false;
        return sub == -1 ? g.count(u) : sub + g.count(u);
    };

    return recur(0);
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

        vector<string> names{c};
        unordered_map<string, int> index{{c, 0}};
        Graph g;

        for (int i = 0; i < n; ++i) {
            string a, b;
            cin >> a >> b;

            int ia = index.count(a) ? index.at(a) : -1;
            if (ia == -1) {
                ia = names.size();
                names.push_back(a);
                index[a] = ia;
            }

            int ib = index.count(b) ? index.at(b) : -1;
            if (ib == -1) {
                ib = names.size();
                names.push_back(b);
                index[b] = ib;
            }

            g.emplace(ia, ib);
        }

        cout << max_coins(names.size(), g) << '\n';
    }

    return 0;
}
