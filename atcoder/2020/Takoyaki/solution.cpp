#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, x, t;
    cin >> n >> x >> t;

    const int complete_batches = n / x;
    const int remainder = n % x;
    const int ans =
        remainder == 0 ? complete_batches * t : (complete_batches + 1) * t;

    cout << ans << '\n';

    return 0;
}
