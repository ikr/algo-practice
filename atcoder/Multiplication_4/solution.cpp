#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
static constexpr ll M = 1e9 + 7;

constexpr int modulo(const ll x) { return ((x % M) + M) % M; }
constexpr int sign(const int x) { return x < 0 ? -1 : 1; }

template <typename T> constexpr bool is_non_negative(const T x) {
    return x >= 0;
}

template <typename T> constexpr bool is_negative(const T x) { return x < 0; }

int modprod_of_k_first(const vi &xs, const int k) {
    return accumulate(
        xs.cbegin(), xs.cbegin() + k, 1LL,
        [](const ll lhs, const ll rhs) { return (lhs * rhs) % M; });
}

optional<pi> non_negative_swap(const vi &xs, const int k) {
    auto it_non_negative =
        find_if(xs.crend() - k, xs.crend(), is_non_negative<int>);
    if (it_non_negative == xs.crend()) return nullopt;

    auto it_negative = find_if(xs.cbegin() + k, xs.cend(), is_negative<int>);
    if (it_negative == xs.cend()) return nullopt;

    return pi{distance(it_non_negative, xs.rend() - 1),
              distance(xs.begin(), it_negative)};
}

optional<pi> negative_swap(const vi &xs, const int k) {
    const auto it_negative =
        find_if(xs.crend() - k, xs.crend(), is_negative<int>);
    if (it_negative == xs.crend()) return nullopt;

    const auto it_non_negative =
        find_if(xs.cbegin() + k, xs.cend(), is_non_negative<int>);
    if (it_non_negative == xs.cend()) return nullopt;

    return pi{distance(it_negative, xs.crend() - 1),
              distance(xs.cbegin(), it_non_negative)};
}

pi optimal_swap(const vi &xs, const pi swapA, const pi swapB) {
    const ll a = xs[swapA.first];
    const ll b = xs[swapA.second];
    const ll c = xs[swapB.first];
    const ll d = xs[swapB.second];

    assert(a != 0 && c != 0);

    const double ra = static_cast<double>(b) / a;
    const double rb = static_cast<double>(c) / d;

    return ra >= rb ? swapA : swapB;
}

int swap_for_positive_product(vi xs, const int k) {
    const ll p = modprod_of_k_first(xs, k);
    if (p >= 0) return p;

    const auto non_negative_pair = non_negative_swap(xs, k);
    const auto negative_pair = negative_swap(xs, k);

    if (non_negative_pair && negative_pair) {
        const auto [i, j] =
            optimal_swap(xs, *non_negative_pair, *negative_pair);
        swap(xs[i], xs[j]);
    } else if (non_negative_pair) {
        const auto [i, j] = *non_negative_pair;
        swap(xs[i], xs[j]);
    } else {
        assert(negative_pair);
        const auto [i, j] = *negative_pair;
        swap(xs[i], xs[j]);
    }

    return modprod_of_k_first(xs, k);
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
