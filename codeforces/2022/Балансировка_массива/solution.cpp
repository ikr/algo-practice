#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int INF = 1'000'000'007;

ll deltas_sum_min(const vector<ll> &A, const vector<ll> &B) {
    vector<ll> dp0(sz(A), INF);
    dp0[0] = 0;
    vector<ll> dp1(sz(A), INF);
    dp1[0] = 0;

    for (int i = 1; i < sz(A); ++i) {
        dp0[i] = min(abs(A[i - 1] - A[i]) + abs(B[i - 1] - B[i]) + dp0[i - 1],
                     abs(B[i - 1] - A[i]) + abs(A[i - 1] - B[i]) + dp1[i - 1]);

        dp1[i] = min(abs(A[i - 1] - B[i]) + abs(B[i - 1] - A[i]) + dp0[i - 1],
                     abs(B[i - 1] - B[i]) + abs(A[i - 1] - A[i]) + dp1[i - 1]);
    }

    return min(dp0.back(), dp1.back());
}

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

        vector<ll> B(n);
        for (auto &b : B) cin >> b;

        cout << deltas_sum_min(A, B) << '\n';
    }

    return 0;
}
