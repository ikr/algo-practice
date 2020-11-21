#include <bits/stdc++.h>
using namespace std;

bool can_be_good(const string &s, const int l, const int r) {
    for (int d = 1; d <= r - l; ++d) {
        const string front = s.substr(l, d);
        const int lo = s.find(front);
        if (lo < l - 1) return true;

        const string back = s.substr(r - d + 1, d);
        const auto hi = s.find(back, r - d + 2);
        if (hi != string::npos) return true;
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        string bits(n, ' ');
        cin >> bits;

        for (int i = 0; i < q; ++i) {
            int l, r;
            cin >> l >> r;
            --l;
            --r;

            cout << (can_be_good(bits, l, r) ? "YES\n" : "NO\n");
        }
    }

    return 0;
}
