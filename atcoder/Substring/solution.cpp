#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s, t;
    cin >> s >> t;

    const int ssz = s.size();
    const int tsz = t.size();

    int ans = INT_MAX;

    for (int i = 0; i + tsz - 1 < ssz; ++i) {
        int candidate = 0;

        for (int j = 0; j < tsz; ++j) {
            if (s[i + j] != t[j]) {
                ++candidate;
            }
        }

        ans = min(ans, candidate);
    }

    cout << ans << '\n';

    return 0;
}
