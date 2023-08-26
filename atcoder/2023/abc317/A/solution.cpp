#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, H, X;
    cin >> N >> H >> X;

    vector<int> P(N);
    for (auto &p : P) cin >> p;

    const auto ans = [&]() -> int {
        for (int i = 0; i < N; ++i) {
            if (H + P[i] >= X) return i + 1;
        }

        return 0;
    }();

    cout << ans << '\n';
    return 0;
}
