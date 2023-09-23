#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll max_K(const ll A, const ll B, const ll C) { return 0; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        ll A, B, C;
        cin >> A >> B >> C;

        cout << "Case #" << i << ": " << max_K(A, B, C) << '\n';
    }

    return 0;
}
