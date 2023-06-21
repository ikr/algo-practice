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

        map<ull, map<ll, int>> freq;
        for (const auto &x : xs) {
            ++(freq[mlog2(x)][x]);
        }

        const auto &hi = crbegin(freq)->second;
        int result = 1;
        for (const auto &[_, f] : hi) {
            result = max(result, f);
        }

        cout << result << '\n';
    }

    return 0;
}
