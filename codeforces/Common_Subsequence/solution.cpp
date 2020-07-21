#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        unordered_set<int> xs;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            xs.insert(x);
        }

        int match = 0;
        for (int i = 0; i < m; ++i) {
            int y;
            cin >> y;

            if (!match && xs.count(y)) {
                match = y;
            }
        }

        if (match) {
            cout << "YES\n1 " << match << '\n';
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
