#include <bits/stdc++.h>
using namespace std;

tuple<int, int, int> dist(const int n) {
    for (int i = 0; i <= n / 3; ++i) {
        if (i * 3 > n) return {-1, -1, -1};

        for (int j = 0; j <= n / 5; ++j) {
            if (i * 3 + j * 5 > n) break;

            for (int k = 0; k <= n / 7; ++k) {
                const int x = i * 3 + j * 5 + k * 7;
                if (x > n) break;
                if (x == n) return {i, j, k};
            }
        }
    }

    return {-1, -1, -1};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        const auto [i, j, k] = dist(n);
        if (i == -1) {
            cout << -1;
        } else {
            cout << i << ' ' << j << ' ' << k;
        }
        cout << '\n';
    }

    return 0;
}
