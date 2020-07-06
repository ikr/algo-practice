#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using ll = long long;

ll max_total_comfort(vi xs) {
    sort(xs.begin(), xs.end(), greater<int>{});
    return accumulate(xs.cbegin(), xs.cend() - 1, 0LL);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    vi xs(t, 0);
    for (auto &x : xs) cin >> x;

    cout << max_total_comfort(xs) << '\n';

    return 0;
}
