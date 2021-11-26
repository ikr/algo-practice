#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

constexpr ll num_substrings(const ll n) { return n * (n + 1LL) / 2LL; }

ll min_f(const int n, const int m) {
    if (n == m) return 0;
    if (m == 0) return num_substrings(n);

    const ll zeros = n - m;
    if (zeros <= m + 1LL) return zeros;

    if (zeros % (m + 1LL) == 0LL) {
        const ll span = zeros / (m + 1LL);
        return (m + 1LL) * num_substrings(span);
    }

    const ll span = (zeros + 1LL) / (m + 1LL);
    const ll rem = zeros - m * span;
    return m * num_substrings(span) + num_substrings(rem);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        cout << min_f(n, m) << '\n';
    }

    return 0;
}
