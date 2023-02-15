#include <bits/stdc++.h>
using namespace std;

int min_ops(array<int, 3> xs) {
    if (xs[0] == xs[1] && xs[1] == xs[2]) return 0;

    sort(begin(xs), end(xs));
    if (xs[0] != xs[1]) return -1;

    const auto d = xs[2] - xs[1];
    return (d % 2) == 0 ? (d / 2) : -1;
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
