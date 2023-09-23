#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll total_price_of_all_set_meals(const vector<ll> &A, const vector<ll> &B,
                                const ll P) {
    vector<ll> ss(sz(B));
    partial_sum(cbegin(B), cend(B), begin(ss));

    ll result{};
    for (const auto a : A) {
        const ll i = upper_bound(cbegin(B), cend(B), P - a) - cbegin(B);
        if (i > 0LL) result += a * i + ss[i - 1];

        const ll m = sz(B) - i;
        result += P * m;
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    ll P;
    cin >> N >> M >> P;

    vector<ll> A(N);
    for (auto &a : A) cin >> a;

    vector<ll> B(M);
    for (auto &b : B) cin >> b;
    ranges::sort(B);

    cout << total_price_of_all_set_meals(A, B, P) << '\n';
    return 0;
}
