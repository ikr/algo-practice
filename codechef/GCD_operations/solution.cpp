#include <bits/stdc++.h>
using namespace std;

bool is_possible(const vector<int> &xs) {
    const int n = xs.size();

    for (int i = 1; i <= n; ++i) {
        const int b = xs[i - 1];
        if (i % b != 0) return false;
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << (is_possible(xs) ? "YES\n" : "NO\n");
    }

    return 0;
}
