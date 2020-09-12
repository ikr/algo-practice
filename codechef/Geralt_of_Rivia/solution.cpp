#include <bits/stdc++.h>
using namespace std;
using Graph = unordered_multimap<char, char>;
constexpr int SZ = CHAR_MAX + 1;

int max_coins(const char s, Graph &g) {
    vector<bool> discovered(SZ, false);
    int ans = 0;
    function<void(int)> recur;

    recur = [&](const char u) {
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        char c;
        cin >> c;

        Graph g;
        for (int i = 0; i < n; ++i) {
            char a, b;
            cin >> a >> b;
            g.emplace(a, b);
        }

        cout << max_coins(c, g) << '\n';
    }

    return 0;
}
