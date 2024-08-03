#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    auto ys = xs;
    sort(rbegin(ys), rend(ys));

    for (int i = 0; i < n; ++i) {
        if (xs[i] == ys[1]) {
            cout << (i + 1) << '\n';
            break;
        }
    }
    return 0;
}
