#include <atcoder/fenwicktree>
#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint998244353;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<mint> progressive_expected_max_of_two_pulls(const vector<int> &xs) {
    const auto x_max = *max_element(cbegin(xs), cend(xs));
    atcoder::fenwick_tree<int> ft_fq(x_max + 1);
    atcoder::fenwick_tree<mint> ft_vl(x_max + 1);

    vector<mint> result(sz(xs), xs[0]);
    ft_fq.add(xs[0], 1);
    ft_vl.add(xs[0], xs[0]);

    for (int i = 1; i < sz(result); ++i) {
        const auto K = i + 1;
        const auto P =
            ft_vl.sum(0, xs[i]) + mint{K - ft_fq.sum(0, xs[i])} * xs[i];
        const auto Q = mint{K} * mint{K};

        result[i] = P * Q.inv();
        ft_fq.add(xs[i], 1);
        ft_vl.add(xs[i], xs[i]);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    for (const auto p_over_q : progressive_expected_max_of_two_pulls(xs)) {
        cout << p_over_q.val() << '\n';
    }
    return 0;
}
