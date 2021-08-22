#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint1000000007;
using mint_ = atcoder::static_modint<1000000007 - 1>;

static constexpr int N_MAX = 100'000;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> vector<T> sufficient_fib_seq() {
    vector<T> ans(N_MAX + 2, 0);
    ans[1] = 1;

    for (int i = 2; i < sz(ans); ++i) {
        ans[i] = ans[i - 1] + ans[i - 2];
    }

    return ans;
}

int all_seq_digits_sum(const vector<mint> &fib, const vector<mint_> &fib_,
                       const int n) {
    const auto e = (fib_[n  + 1] - mint_{1}).val();
    const auto ans = mint{2}.pow(e) * fib[n];
    return ans.val();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const auto fib = sufficient_fib_seq<mint>();
    const auto fib_ = sufficient_fib_seq<mint_>();

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << all_seq_digits_sum(fib, fib_, n) << '\n';
    }

    return 0;
}
