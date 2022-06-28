#include <iostream>
using namespace std;

using ll = long long;

ll solve(const ll L, const ll R) {
    const auto p = min(L, R);
    return (p * (p + 1LL)) / 2LL;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int L, R;
        cin >> L >> R;
        cout << "Case #" << i << ": " << solve(L, R) << '\n';
    }

    return 0;
}
