#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool is_possible(const array<ll, 3> &xs) {
    const auto [a, b, c] = xs;

    if (b % a || c % a) return false;

    ll cuts{};
    if (a != b) {
        cuts += b / a - 1LL;
    }

    if (a != c) {
        cuts += c / a - 1LL;
    }
    return cuts <= 3;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        array<ll, 3> xs;
        for (auto &x : xs) cin >> x;
        ranges::sort(xs);

        cout << (is_possible(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
