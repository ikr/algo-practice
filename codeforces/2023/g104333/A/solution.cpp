#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint1000000007;
using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

array<int, 30> freqs_by_bit(const vector<int> &xs) {
    array<int, 30> ans;
    ans.fill(0);

    for (const auto x : xs) {
        for (int i = 0; i < sz(ans); ++i) {
            if (x & (1 << i)) {
                ++ans[i];
            }
        }
    }

    return ans;
}

// See https://stackoverflow.com/a/21389244/6430
mint sum_of_pairwise_xors(const vector<int> &A, const vector<int> &B) {
    const int n = sz(A);
    const auto fa = freqs_by_bit(A);
    const auto fb = freqs_by_bit(B);

    mint ans{};
    for (int i = 0; i < sz(fa); ++i) {
        const mint a = fa[i];
        const mint a_ = n - fa[i];

        const mint b = fb[i];
        const mint b_ = n - fb[i];

        const mint m = (1 << i);

        ans += m * ((a * b_) + (a_ * b));
    }
    return ans;
}

mint mega_sum(const vector<int> &A, const vector<int> &B) {
    const auto n = sz(A);
    assert(sz(A) == sz(B));

    mint n_1_fact = 1;
    for (int i = 1; i <= n - 1; ++i) {
        n_1_fact *= i;
    }

    return n_1_fact * sum_of_pairwise_xors(A, B);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> A(n);
    for (auto &a : A) cin >> a;

    vector<int> B(n);
    for (auto &b : B) cin >> b;

    cout << mega_sum(A, B).val() << '\n';
    return 0;
}
