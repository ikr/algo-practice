#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int intof(const T x) {
    return static_cast<int>(x);
}

constexpr int mmax(const int x, const int y) { return max(x, y); }
constexpr int e() { return 0; }

int solve(const vector<int> &xs, const int k) {
    const int hi = *max_element(cbegin(xs), cend(xs));
    atcoder::segtree<int, mmax, e> max_lengths_by_val(hi + 1);

    for (const int x : xs) {
        const int h =
            max_lengths_by_val.prod(max(0, x - k), min(hi + 1, x + k));
        max_lengths_by_val.set(x, h + 1);
    }

    return max_lengths_by_val.all_prod();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, K;
    cin >> N >> K;

    vector<int> xs(N, 0);
    for (auto &x : xs) cin >> x;

    cout << solve(xs, K) << '\n';

    return 0;
}
