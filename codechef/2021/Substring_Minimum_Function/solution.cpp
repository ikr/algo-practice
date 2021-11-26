#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll num_substrings(const ll n) { return n * (n + 1LL) / 2LL; }

ll min_f(const int n, const int m) {
    if (n == m) return 0;
    if (m == 0) return num_substrings(n);

    const ll z = n - m;
    const ll a = z / (m + 1LL);
    const ll b = z % (m + 1LL);

    return b * num_substrings(a + 1) + (m + 1 - b) * num_substrings(a);
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
