#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using oi = optional<int>;
static constexpr ll M = 1e9 + 7;

constexpr int modulo(const ll x) { return ((x % M) + M) % M; }
constexpr int sign(const int x) { return x < 0 ? -1 : 1; }

oi product_after_replace_positive(vi xs, const int k) { return nullopt; }

oi product_after_replace_negative(vi xs, const int k) { return nullopt; }

constexpr int omax(const oi x, const oi y) {
    if (!!x && !!y) return max(*x, *y);
    return !!x ? *x : *y;
}

int swap_for_positive_product(const vi &xs, const int k) {
    const ll p =
        accumulate(xs.cbegin(), xs.cbegin() + k, 1LL,
                   [](const ll lhs, const ll rhs) { return (lhs * rhs) % M; });

    if (p >= 0) return p;

    return omax(product_after_replace_positive(xs, k),
                product_after_replace_negative(xs, k));
}

int max_product(vi &xs, const int k) {
    const int sz = xs.size();

    sort(xs.begin(), xs.end(),
         [](const int lhs, const int rhs) { return abs(lhs) > abs(rhs); });

    const int negative =
        count_if(xs.cbegin(), xs.cend(), [](const int x) { return x < 0; });

    if (k == sz || (negative == sz && k % 2))
        return accumulate(
            xs.crbegin(), xs.crbegin() + k, 1LL,
            [](const ll lhs, const ll rhs) { return modulo(lhs * rhs); });

    if (k == 1) return modulo(*max_element(xs.cbegin(), xs.cend()));

    return swap_for_positive_product(xs, k);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz, k;
    cin >> sz >> k;
    vi xs(sz, 0);
    for (auto &x : xs) cin >> x;

    cout << max_product(xs, k) << '\n';

    return 0;
}
