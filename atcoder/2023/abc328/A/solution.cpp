#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, X;
    cin >> N >> X;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    int ans{};
    for (const auto x : xs) {
        if (x <= X) ans += x;
    }

    cout << ans << '\n';
    return 0;
}
