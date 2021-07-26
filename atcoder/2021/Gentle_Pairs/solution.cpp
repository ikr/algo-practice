#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pair<int, int>> ps(n);
    for (auto &[x, y] : ps) {
        cin >> x >> y;
    }

    sort(begin(ps), end(ps));
    int ans = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            const int dy = ps[j].second - ps[i].second;
            const int dx = ps[j].first - ps[i].first;

            if (-dx <= dy && dy <= dx) ++ans;
        }
    }

    cout << ans << '\n';
    return 0;
}
