#include <bits/stdc++.h>
using namespace std;

bool possible(const int a, const int b, const int c) {
    if ((a + b + c) % 9 != 0) return false;
    const int k = (a + b + c) / 9;
    return a >= k;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        vector<int> xs(3, 0);
        cin >> xs[0] >> xs[1] >> xs[2];
        sort(begin(xs), end(xs));
        cout << (possible(xs[0], xs[1], xs[2]) ? "YES\n" : "NO\n");
    }

    return 0;
}
