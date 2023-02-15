#include <bits/stdc++.h>
using namespace std;

int min_ops(array<int, 3> xs) {
    if (xs[0] == xs[1] && xs[1] == xs[2]) return 0;

    if (any_of(cbegin(xs), cend(xs), [](const int x) { return x % 2; })) {
        return -1;
    }

    sort(begin(xs), end(xs));
    if (xs[0] == xs[1]) {
        const auto d = xs[2] - xs[1];
        return d / 2;
    }

    int o0 = (xs[1] - xs[0]) / 2;
    xs[2] += o0 * 2;

    const auto d = xs[2] - xs[1];
    return o0 + d / 2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int A, B, C;
        cin >> A >> B >> C;

        const auto lo = min({A, B, C});
        A -= lo;
        B -= lo;
        C -= lo;

        cout << min_ops({A, B, C}) << '\n';
    }

    return 0;
}
