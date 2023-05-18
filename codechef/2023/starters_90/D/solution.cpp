#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint1000000007;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static const auto FACT = []() {
    vector<mint> result(10001, 1);
    for (int i = 2; i < sz(result); ++i) result[i] = result[i - 1] * i;
    return result;
}();

mint n_choose_k(const int n, const int k) {
    return FACT[n] * (FACT[k] * FACT[n - k]).inv();
}

mint goodness_sum(const vector<int> &xs) {
    const auto N = sz(xs);
    mint result{};

    for (int i0{}; i0 < N; ++i0) {
        const auto i = i0 + 1;
        const auto x = xs[i0];

        if (x > i) continue;
        const auto pre = i - 1;
        const auto suf = N - i;

        result += n_choose_k(pre, x - 1) * mint{2}.pow(suf);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        cout << goodness_sum(xs).val() << '\n';
    }

    return 0;
}
