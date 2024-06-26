#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll num_ways(const ll M, const vector<ll> &A, const vector<ll> &B) {
    const ll n = sz(A);
    if (M == 1) return n * n;

    map<ll, int> bfq;
    for (const auto b : B) ++bfq[b % M];

    ll result{};
    for (const auto a : A) {
        const auto b = ((M - (a % M)) + M) % M;
        const auto it = bfq.find(b);
        if (it != cend(bfq)) {
            result += it->second;
        } else {
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
        int n, m;
        cin >> n >> m;

        vector<ll> A(n);
        for (auto &a : A) cin >> a;

        vector<ll> B(n);
        for (auto &b : B) cin >> b;

        cout << num_ways(m, A, B) << '\n';
    }

    return 0;
}
