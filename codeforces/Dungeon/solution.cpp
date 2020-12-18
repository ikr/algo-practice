#include <bits/stdc++.h>
using namespace std;

bool possible(const int a, const int b, const int c) {
    if (!a) return false;

    if (a == b && b == c) {
        return a >= 3 && (b % 3 == 0);
    }

    if (a - 1 >= 3) {
        const int k = (a - 1) / 3;
        return possible(a - k * 3, b - k * 3, c - k * 3);
    }

    const int k = (c - a) / 7;
    if (a < k) return false;
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
