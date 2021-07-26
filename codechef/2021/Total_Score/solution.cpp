#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> ss(k);
        for (auto &s : ss) cin >> s;

        vector<string> rs(n);
        for (auto &r : rs) {
            cin >> r;

            long long ans = 0;
            for (int i = 0; i < k; ++i) {
                if (r[i] == '1') ans += ss[i];
            }

            cout << ans << '\n';
        }
    }

    return 0;
}
