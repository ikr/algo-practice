#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int i = 0; i != T; ++i) {
        int n;
        cin >> n;

        int p0 = -1;
        int c0 = -1;

        bool ok = true;

        for (int j = 0; j != n; ++j) {
            int p, c;
            cin >> p >> c;
            if (!ok) continue;

            if (c > p) ok = false;

            if (p0 >= 0) {
                const int dp = p - p0;
                const int dc = c - c0;

                if (!(dp >= 0 && dc >= 0 && dc <= dp)) ok = false;
            }

            p0 = p;
            c0 = c;
        }

        cout << (ok ? "YES" : "NO") << endl;
    }

    return 0;
}
