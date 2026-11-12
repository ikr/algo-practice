#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;

        vector<int> xs{a, b, c};
        ranges::sort(xs);
        const bool result = xs[0] + 1 == xs[1] && xs[1] + 1 == xs[2];
        cout << (result ? "YES" : "NO") << '\n';
    }

    return 0;
}
