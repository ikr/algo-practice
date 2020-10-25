#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;

    vector<int> ys(n, 0);
    for (auto &y : ys) cin >> y;

    atcoder::dsu g(n);

    for (int i = 0; i < m; ++i) {
        int c, d;
        cin >> c >> d;
        --c;
        --d;
        g.merge(c, d);
    }

    const auto components = g.groups();
    bool ans = true;
    for (const auto &co : components) {
        ll s1 = 0;
        ll s2 = 0;

        for (const auto i : co) {
            s1 += xs[i];
            s2 += ys[i];
        }

        if (s1 != s2) {
            ans = false;
            break;
        }
    }

    cout << (ans ? "Yes\n" : "No\n");
    return 0;
}
