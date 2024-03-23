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

    vector<ll> ltr0(N, 0);
    vector<ll> ltr1(N, 0);

    if (S[0] == '0') {
        ltr1[0] = C[0];
    } else {
        assert(S[0] == '1');
        ltr0[0] = C[0];
    }

    for (int i = 1; i < N; ++i) {
        if (S[i] == '0') {
            ltr0[i] = ltr1[i - 1];
            ltr1[i] = ltr0[i - 1] + C[i];
        } else {
            assert(S[i] == '1');
            ltr1[i] = ltr0[i - 1];
            ltr0[i] = ltr1[i - 1] + C[i];
        }
    }

    vector<ll> rtl0(N, 0);
    vector<ll> rtl1(N, 0);

    if (S.back() == '0') {
        rtl1.back() = C.back();
    } else {
        assert(S.back() == '1');
        rtl0.back() = C.back();
    }

    for (int i = N - 2; i >= 0; --i) {
        if (S[i] == '0') {
            rtl0[i] = rtl1[i + 1];
            rtl1[i] = rtl0[i + 1] + C[i];
        } else {
            assert(S[i] == '1');
            rtl1[i] = rtl0[i + 1];
            rtl0[i] = rtl1[i + 1] + C[i];
        }
    }

    ll result = LONG_LONG_MAX;
    for (int i = 1; i < N; ++i) {
        { // taking 0 at i
            const ll pre = ltr0[i - 1];
            const ll post = (i == N - 1) ? 0 : rtl1[i + 1];
            const ll c = S[i] == '0' ? 0 : C[i];
            result = min(result, pre + c + post);
        }

        { // taking 1 at i
            const ll pre = ltr1[i - 1];
            const ll post = (i == N - 1) ? 0 : rtl0[i + 1];
            const ll c = S[i] == '1' ? 0 : C[i];
            result = min(result, pre + c + post);
        }
    }
    cout << result << '\n';
    return 0;
}
