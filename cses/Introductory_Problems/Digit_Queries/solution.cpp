#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr ll mpow(const ll base, const ll exp) {
    if (!exp) return 1;
    if (exp % 2LL) return base * mpow(base, exp - 1);
    const auto q = mpow(base, exp / 2LL);
    return q * q;
}

vll milestones() {
    vll ans{0};
    for (ll i = 1; i <= 17; ++i) {
        ans.push_back(ans.back() + 9LL * mpow(10, i - 1) * i);
    }
    return ans;
}

int block_size(const vll &ms, const ll k) {
    const auto it = lower_bound(cbegin(ms), cend(ms), k);
    return inof(distance(cbegin(ms), it));
}

int kth_digit(const ll x, const int k) {
    assert(k >= 0);

    stringstream ss;
    ss << x;
    const string xs = ss.str();

    assert(sz(xs) >= 0 && k < sz(xs));
    return inof(xs[k] - '0');
}

int kth_digit_in_seq(const vll &ms, const ll k) {
    const auto bs = block_size(ms, k);
    assert(bs < sz(ms));

    const auto i = k - ms[bs - 1] - 1;
    const auto block_index = i / llof(bs);
    const auto digit_index = i % llof(bs);
    assert(digit_index < bs);

    const auto block_value = mpow(10, bs - 1) + block_index;
    return kth_digit(block_value, inof(digit_index));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const auto ms = milestones();

    int q;
    cin >> q;
    while (q--) {
        ll k;
        cin >> k;
        cout << kth_digit_in_seq(ms, k) << '\n';
    }

    return 0;
}
