#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll num_meeting_pairs(const ll T, const vector<ll> &ltr, const vector<ll> &rtl) {
    ll result{};
    for (const auto x : ltr) {
        const auto j = inof(upper_bound(cbegin(rtl), cend(rtl), x + 2LL * T) -
                            cbegin(rtl));
        const auto i =
            inof(lower_bound(cbegin(rtl), cend(rtl), x) - cbegin(rtl));
        assert(j >= i);
        result += j - i;
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    ll T;
    cin >> N >> T;

    string S;
    cin >> S;
    assert(sz(S) == N);

    vector<ll> X(N);
    for (auto &x : X) cin >> x;

    vector<ll> ltr;
    vector<ll> rtl;
    for (int i = 0; i < N; ++i) {
        if (S[i] == '0') {
            // Negative direction
            rtl.push_back(X[i]);
        } else {
            assert(S[i] == '1'); // Positive direction
            ltr.push_back(X[i]);
        }
    }
    sort(begin(ltr), end(ltr));
    sort(begin(rtl), end(rtl));

    cout << num_meeting_pairs(T, ltr, rtl) << '\n';
    return 0;
}
