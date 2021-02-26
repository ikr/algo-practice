#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

int total_overlap(vector<pi> xs, vector<pi> ys) { return -1; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<pi> xs(n);
        for (auto &[a, b] : xs) cin >> a >> b;

        vector<pi> ys(m);
        for (auto &[a, b] : ys) cin >> a >> b;

        cout << total_overlap(move(xs), move(ys)) << '\n';
    }

    return 0;
}
