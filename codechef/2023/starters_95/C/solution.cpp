#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr unsigned long long mlog2(const unsigned long long x) {
    return 8ULL * sizeof(unsigned long long) - __builtin_clzll(x) - 1ULL;
}

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<ll> xs(n);
        for (auto &x : xs) cin >> x;

        map<ull, int> freq;
        for (const auto &x : xs) {
            ++freq[mlog2(x)];
        }

        const auto hi = crbegin(freq)->second;
        cout << div_ceil(hi, 2) << '\n';
    }

    return 0;
}
