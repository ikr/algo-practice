#include <bits/stdc++.h>

using namespace std;

constexpr double real_y(const long r, const long x) {
    return ((r - 1.0) / x - (x + 1.0)) / 2.0;
}

constexpr optional<long> integer_y(const long r, const long x) {
    if ((r - 1L) % x) return nullopt;
    const long twice_as_much = (r - 1L) / x - (x + 1L);
    if (twice_as_much % 2L) return nullopt;
    return {twice_as_much / 2L};
}

int main() {
    long r;
    cin >> r;

    for (long x = 1L;; ++x) {
        if (real_y(r, x) < 0.0) {
            cout << "NO\n";
            break;
        }

        const auto y_value = integer_y(r, x);
        if (!y_value || (*y_value) == 0L) continue;

        cout << x << ' ' << (*y_value) << '\n';
        break;
    }

    return 0;
}
