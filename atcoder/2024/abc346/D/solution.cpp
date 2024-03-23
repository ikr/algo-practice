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

    string S;
    cin >> S;

    vector<ll> C(N);
    for (auto &c : C) cin >> c;

    vector<ll> dp0(N, 0);
    vector<ll> dp1(N, 0);

    if (S[0] == '0') {
        dp1[0] = C[0];
    } else {
        assert(S[0] == '1');
        dp0[0] = C[0];
    }

    for (int i = 1; i < N; ++i) {
        if (S[i] == '0') {
            dp1[i] = C[i];
        } else {
            assert(S[i] == '1');
            dp0[i] = C[i];
        }
    }

    vector<ll> ss0(N + 1, 0);
    partial_sum(cbegin(dp0), cend(dp0), begin(ss0) + 1);
    vector<ll> ss1(N + 1, 0);
    partial_sum(cbegin(dp1), cend(dp1), begin(ss1) + 1);

    ll result = LONG_LONG_MAX;
    for (int i = 1; i < N; ++i) {
        { // taking 0 at i
            const ll pre = dp0[i - 1];
        }

        { // taking 1 at i
        }
    }
    cout << result << '\n';
    return 0;
}
