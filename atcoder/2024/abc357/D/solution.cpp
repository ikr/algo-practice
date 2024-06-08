#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using mint = atcoder::modint998244353;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N;
    cin >> N;

    const auto m = sz(to_string(N));
    const auto r = mint{10}.pow(m);
    const auto a = mint{N};

    const mint result = a * (mint{1} - r.pow(N)) * (mint{1} - r).inv();
    cout << result.val() << '\n';
    return 0;
}
