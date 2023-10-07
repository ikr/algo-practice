#include <bits/stdc++.h>
using namespace std;

bool alice_wins_for_sure(const int H, const int W) { return H > W; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int H, W, A, B;
        cin >> H >> W >> A >> B;

        cout << "Case #" << i << ": "
             << (alice_wins_for_sure(H, W) ? "YES" : "NO") << '\n';
    }

    return 0;
}
