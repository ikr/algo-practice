#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    vector<int> xs(7);
    for (auto &x : xs) cin >> x;

    int result = INT_MIN;
    for (int bits = 0; bits < (1 << 6); ++bits) {
        int cur = xs[0];
        for (int j = 0; j < 6; ++j) {
            if (bits & (1 << j)) {
                cur += xs[j + 1];
            } else {
                cur -= xs[j + 1];
            }
        }
        result = max(result, cur);
    }
    cout << result << '\n';
    return 0;
}
