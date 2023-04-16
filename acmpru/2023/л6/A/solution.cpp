#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    array<int, 3> xs{};
    for (auto &x : xs) cin >> x;

    auto ys = xs;
    sort(begin(xs), end(xs));

    int diffs{};
    for (int i = 0; i < 3; ++i) {
        diffs += xs[i] != ys[i];
    }

    const auto ans = diffs ? diffs - 1 : 0;
    cout << ans << '\n';
    return 0;
}
