#include <algorithm>
#include <bits/stdc++.h>
#include <numeric>
using namespace std;
using ll = long long;
using vi = vector<int>;
static constexpr ll M = 1e9 + 7;

template <typename T> constexpr int intof(const T x) {
    return static_cast<int>(x);
}

constexpr int modulo(const ll x) { return ((x % M) + M) % M; }

pair<vi, vi> sorted_sign_groups(const vi &xs) {
    vi negative;
    vi positive;

    for (const auto x : xs) {
        if (x < 0)
            negative.push_back(x);
        else if (x > 0)
            positive.push_back(x);
    }

    sort(negative.begin(), negative.end(), greater<int>{});
    sort(positive.begin(), positive.end(), greater<int>{});

    return {negative, positive};
}

int max_product(const vi &xs, const int k) {
    const int sz = xs.size();

    if (k == sz) {
        return accumulate(
            xs.cbegin(), xs.cend(), 1LL,
            [](const ll lhs, const ll rhs) { return modulo(lhs * rhs); });
    }

    if (k == 1) return modulo(*max_element(xs.cbegin(), xs.cend()));

    const auto [negative, positive] = sorted_sign_groups(xs);
    if (intof(negative.size() + positive.size()) < k) return 0;

    return -1;
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
