#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_points(vll &A, vll &B) {
    partial_sum(cbegin(A), cend(A), begin(A));
    partial_sum(cbegin(B), cend(B), begin(B));

    ll ans = 0;

    for (int i = 0; i < sz(A); ++i) {
        ans += A[i] - B[i];
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vll A(n);
        for (auto &a : A) cin >> a;

        vll B(n);
        for (auto &b : B) cin >> b;

        cout << max_points(A, B) << '\n';
    }

    return 0;
}
