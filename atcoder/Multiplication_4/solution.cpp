#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
static constexpr ll M = 1e9 + 7;

constexpr int modulo(const ll x) { return ((x % M) + M) % M; }
constexpr int sign(const int x) { return x < 0 ? -1 : 1; }

int swap_for_positive_product(vi &xs, const int k) {
    const ll p =
        accumulate(xs.cbegin(), xs.cbegin() + k, 1LL,
                   [](const ll lhs, const ll rhs) { return (lhs * rhs) % M; });

    if (p >= 0) return p;

    int i = k - 1, j = k;
    while (sign(xs[i]) == sign(xs[j])) {
        --i;
        ++j;
    }

    swap(xs[i], xs[j]);
    return accumulate(
        xs.cbegin(), xs.cbegin() + k, 1LL,
        [](const ll lhs, const ll rhs) { return modulo(lhs * rhs); });
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
