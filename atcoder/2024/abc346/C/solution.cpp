#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    ll K;
    cin >> K;

    vector<ll> A(N);
    for (auto &a : A) cin >> a;

    unordered_set<ll> aset(cbegin(A), cend(A));

    ll result = K * (1LL + K) / 2LL;
    for (const auto a : aset) {
        if (a <= K) result -= a;
    };
    cout << result << '\n';
    return 0;
}
