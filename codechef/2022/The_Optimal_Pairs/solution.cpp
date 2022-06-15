#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using ll = long long;

int solve(const ll N) {
    set<pair<ll, ll>> ds;

    for (ll q = 1; q * q <= N; ++q) {
        if (N % q) continue;
        const auto p = N / q;

        if (min(q, N - q)) ds.emplace(min(q, N - q), max(q, N - q));
        if (min(p, N - p)) ds.emplace(min(p, N - p), max(p, N - p));
    }

    int result{};
    for (const auto &[a, b] : ds) {
        if (a == b) {
            ++result;
        } else {
            result += 2;
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        cout << solve(N) << '\n';
    }

    return 0;
}
