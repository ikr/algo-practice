#include <bits/stdc++.h>
using namespace std;

int make_move(array<int, 3> &ds) {
    if (ds[0] > 0) {
        const int ans = ds[0];
        ds[0] = 0;
        ds[1] += ans;
        return ans;
    }

    if (ds[1] > 0) {
        const int ans = ds[1];
        ds[1] = 0;
        ds[2] += ans;
        return ans;
    }

    if (ds[2] > 0) {
        const int ans = ds[2];
        ds[2] = 0;
        ds[0] += ans;
        return ans;
    }

    assert(false && "/o\\");
    return -1;
}

int min_moves(const vector<int> &xs) {
    array<int, 3> cs{0, 0, 0};
    for (const int x : xs) {
        ++cs[x % 3];
    }

    if (cs[0] == cs[1] && cs[1] == cs[2]) return 0;
    const int t = (cs[0] + cs[1] + cs[2]) / 3;

    int ans = 0;
    array<int, 3> ds{cs[0] - t, cs[1] - t, cs[2] - t};
    while (ds != array<int, 3>{0, 0, 0}) {
        ans += make_move(ds);
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

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << min_moves(xs) << '\n';
    }

    return 0;
}
