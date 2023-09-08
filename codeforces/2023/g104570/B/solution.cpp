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

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<ll> A(n);
        for (auto &a : A) cin >> a;

        const auto X = A.back();
        A.pop_back();
        ranges::reverse(A);

        vector<ll> SA(sz(A));
        partial_sum(cbegin(A), cend(A), begin(SA));

        vector<ll> B(n);
        for (auto &b : B) cin >> b;

        assert(B.back() == X);
        B.pop_back();
        ranges::reverse(B);

        vector<ll> SB(sz(B));
        partial_sum(cbegin(B), cend(B), begin(SB));

        ll ans = X - SB.back();
        for (int i = 0; i < sz(SA); ++i) {
            auto a = SA[i];
            auto b = i ? SB[i - 1] : 0LL;

            if (b + X - a > SB.back() - a - X) {
                ans = max(ans, a - (b + X));
            } else {
                ans = max(ans, a + X - SB.back());
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
