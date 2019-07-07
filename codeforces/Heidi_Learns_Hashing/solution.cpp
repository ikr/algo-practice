#include <bits/stdc++.h>

using namespace std;

using ll_t = long long;

constexpr optional<ll_t> integer_y(const ll_t r, const ll_t x) {
    if ((r - 1L) % x) return nullopt;
    const ll_t twice_as_much = (r - 1L) / x - (x + 1L);
    if (twice_as_much % 2L) return nullopt;
    return {twice_as_much / 2L};
}

int main() {
    ll_t r;
    cin >> r;

    for (ll_t x = 1L;; ++x) {
        if (x > sqrt(r - 1L)) {
            cout << "NO\n";
            break;
        }

        const auto y_value = integer_y(r, x);
        if (!y_value || (*y_value) <= 0L) continue;

        cout << x << ' ' << (*y_value) << '\n';
        break;
    }

    return 0;
}
