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

    int n;
    cin >> n;

    vector<ll> A(n);
    vector<ll> B(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i] >> B[i];
    }

    const auto sa = accumulate(cbegin(A), cend(A), 0LL);
    ll result{};
    for (int i = 0; i < n; ++i) {
        result = max(result, sa - A[i] + B[i]);
    }
    cout << result << '\n';
    return 0;
}
