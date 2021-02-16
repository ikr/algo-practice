#include <bits/stdc++.h>
using namespace std;

int div_ceil(const int x, const int y) { return x % y ? x / y + 1 : x / y; }

int to_add(const vector<int> &xs) {
    const int n = xs.size();
    int ans = 0;
    for (int i = 0; i < n - 1; ++i) {
        const int a = min(xs[i], xs[i + 1]);
        const int b = max(xs[i], xs[i + 1]);

        int c = a;
        while (div_ceil(b, c) > 2) {
            c += c;
            ++ans;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << to_add(xs) << '\n';
    }

    return 0;
}
