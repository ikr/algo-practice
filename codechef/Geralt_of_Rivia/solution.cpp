#include <bits/stdc++.h>
using namespace std;
using Graph = unordered_multimap<int, int>;

bool can_reach(const int n, const Graph &g, const int s, const int d) {
    queue<int> q;
    q.push(s);
    vector<bool> discovered(n, false);
    discovered[s] = true;

    while (!q.empty()) {
        const int u = q.front();
        q.pop();
        const auto [first, last] = g.equal_range(u);

        for (auto it = first; it != last; ++it) {
            const int v = it->second;
            if (v == d) return true;
            if (discovered[v]) continue;

            discovered[v] = true;
            q.push(v);
        }
    }

    return false;
}

int max_coins(const int n, const Graph &g) {
    vector<pair<int, int>> cc;
    for (int i = 1; i < n; ++i) {
        cc.emplace_back(g.count(i), i);
    }
    sort(begin(cc), end(cc));

    int ans = g.count(0);
    int curr = 0;
    for (const auto [coins, city] : cc) {

        if (can_reach(n, g, curr, city)) {
            ans += coins;
            curr = city;
        } else {
            break;
        }
    }
    return ans;
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
