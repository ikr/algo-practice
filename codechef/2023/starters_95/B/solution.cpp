#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

ll max_total_energy(const int H, const vector<int> &A, const vector<int> &B) {
    ll result{};

    for (int i = 0; i < min(sz(A), sz(B)); ++i) {
        const auto charging_hours = min(H, div_ceil(A[i], B[i]));
        result += min(A[i], B[i] * charging_hours);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N, M, H;
        cin >> N >> M >> H;

        vector<int> A(N);
        for (auto &a : A) cin >> a;
        sort(rbegin(A), rend(A));

        vector<int> B(M);
        for (auto &b : B) cin >> b;
        sort(rbegin(B), rend(B));

        cout << max_total_energy(H, A, B) << '\n';
    }

    return 0;
}
