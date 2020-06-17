#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        string a;
        cin >> a;

        const int sz = a.size();
        string b{a[0]};
        for (int i = 1; i < sz - 1; i += 2) {
            b += a[i];
        }
        b += a.back();
        cout << b << '\n';
    }

    return 0;
}
