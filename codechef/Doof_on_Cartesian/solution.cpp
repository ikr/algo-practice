#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

vector<int> count_walls(vector<int> ays, const vector<pair<int, int>> &coords) {
    sort(ays.begin(), ays.end());
    const int sz = coords.size();
    vector<int> ans(sz, 0);

    for (int i = 0; i < sz; ++i) {
        const auto [x, y] = coords[i];
        const auto it = lower_bound(ays.cbegin(), ays.cend(), x + y);

        if (it == ays.cend()) {
            ans[i] = ays.size();
        } else if (*it == x + y) {
            ans[i] = -1;
        } else {
            ans[i] = distance(ays.cbegin(), it);
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
        int sz;
        cin >> sz;
        vector<int> ays(sz, 0);
        for (auto &a : ays) cin >> a;

        int q;
        cin >> q;
        vector<pair<int, int>> coords(q, {0, 0});
        for (auto &xy : coords) cin >> xy.first >> xy.second;

        for (const auto ans : count_walls(ays, coords)) cout << ans << '\n';
    }

    return 0;
}
