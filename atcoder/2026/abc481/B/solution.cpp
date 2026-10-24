#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    int result{xs[0] == k};

    for (int i = 1; i < n; i++) {
        const int a = xs[i - 1];
        const int b = xs[i];
        assert(a != b);

        if (b == k || (a < k && k < b) || (b < k && k < a)) {
            ++result;
        }
    }

    cout << result << '\n';
    return 0;
}
