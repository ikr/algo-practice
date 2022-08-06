#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int optimal_prefix_replacements_num(const ll T, const vector<ll> &xs) {
    vector<ll> ss(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    int result{};
    ll opt = ss.back();

    for (int k = 1; k <= sz(xs); ++k) {
        ll curr = k * T + (ss.back() - ss[k - 1]);
        if (curr < opt) {
            result = k;
            opt = curr;
        }
    }

    return result;
}

ll min_post_ops_sum(const ll L, const ll R, vector<ll> A) {
    const auto k1 = optimal_prefix_replacements_num(L, A);
    for (int i = 1; i <= k1; ++i) {
        A[i - 1] = L;
    }

    reverse(begin(A), end(A));
    const auto k2 = optimal_prefix_replacements_num(R, A);
    for (int i = 1; i <= k2; ++i) {
        A[i - 1] = R;
    }

    return accumulate(cbegin(A), cend(A), 0LL);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, L, R;
    cin >> N >> L >> R;

    vector<ll> A(N);
    for (auto &a : A) cin >> a;

    cout << min_post_ops_sum(L, R, move(A)) << '\n';
    return 0;
}
