#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
static constexpr double PI = 3.14159265358979323846;

double shortest_walk(const pii A, const pii B) {
    const auto [xa, ya] = A;
    const auto [xb, yb] = B;

    if (xa == 0 && xa == xb) return abs(ya - yb);
    if (ya == 0 && ya == yb) return abs(xa - xb);

    auto r = INT_MAX;
    auto R = 0;
    for (const auto v : {xa, ya, xb, yb}) {
        if (!v) continue;
        r = min(r, abs(v));
        R = max(R, abs(v));
    }

    return PI * r / 2.0 + (R - r + 0.0);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(6) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int xa, ya, xb, yb;
        cin >> xa >> ya >> xb >> yb;

        cout << shortest_walk({xa, ya}, {xb, yb}) << '\n';
    }

    return 0;
}
