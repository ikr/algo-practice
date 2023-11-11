#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    int ans{};
    for (int digit = 1; digit <= 9; ++digit) {
        for (const auto x : vector{digit, digit * 10 + digit}) {
            for (int m = 1; m <= N; ++m) {
                if (m != digit && m != digit * 10 + digit) continue;
                const auto hi = xs[m - 1];
                if (x <= hi) ++ans;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
