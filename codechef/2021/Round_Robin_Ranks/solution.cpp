#include <bits/stdc++.h>
using namespace std;

constexpr int kth_max_points(const int n, const int k) {
    return 2 * max(n - k, n - k + (k - 1) / 2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        cout << kth_max_points(n, k) << '\n';
    }

    return 0;
}
