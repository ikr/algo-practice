#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr unsigned long long mlog2(const unsigned long long x) {
    return 8ULL * sizeof(unsigned long long) - __builtin_clzll(x) - 1ULL;
}

ll ops_num(const ll x) {
    if (x == 0) return 0;
    if (((x + 1LL) & x) == 0LL) return 1;

    const auto e = mlog2(x);

    return ((1LL << (e + 1)) - 1 - x) + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    cout << ops_num(N) << '\n';
    return 0;
}
