#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using mint = atcoder::modint998244353;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

mint num_ways(const vector<pii> &cards) {
    vector<mint> D0(sz(cards), 1);
    vector<mint> D1(sz(cards), 1);

    for (int i = 1; i < sz(D0); ++i) {
        D0[i] = 0;
        if (cards[i - 1].first != cards[i].first) D0[i] += D0[i - 1];
        if (cards[i - 1].second != cards[i].first) D0[i] += D1[i - 1];

        D1[i] = 0;
        if (cards[i - 1].first != cards[i].second) D1[i] += D0[i - 1];
        if (cards[i - 1].second != cards[i].second) D1[i] += D1[i - 1];
    }

    return D0.back() + D1.back();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<pii> cards(N);
    for (auto &[a, b] : cards) cin >> a >> b;

    cout << num_ways(cards).val() << '\n';
    return 0;
}
