#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint1000000007;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

mint mega_sum(const vector<int> &A, const vector<int> &B) {
    const auto n = sz(A);
    assert(sz(A) == sz(B));

    mint n_1_fact = 1;
    for (int i = 1; i <= n - 1; ++i) {
        n_1_fact *= i;
    }

    const auto s =
        accumulate(cbegin(A), cend(A), 0,
                   [](const int agg, const int a) { return agg ^ a; });

    mint ans{0};
    for (const auto b : B) {
        for (const auto a : A) {
            ans += n_1_fact * (b ^ a);
        }
    }
    return ans;
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
