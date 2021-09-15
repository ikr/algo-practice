#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi digits_reversed(const ll x) {
    if (!x) return {0};

    vi ans;
    ll r = x;

    while (r) {
        ans.push_back(inof(r % 10LL));
        r /= 10LL;
    }

    return ans;
}

vi digits(const ll x) {
    auto ans = digits_reversed(x);
    reverse(begin(ans), end(ans));
    return ans;
}

vector<array<ll, 10>> sought_nums_up_to(const ll hi) {
    const auto ds = digits(hi);

    // D[i][j] is # of sought ints having i digits, with the 1st digit being j
    vector<array<ll, 10>> dp(sz(ds) + 1, array<ll, 10>{});

    return dp;
}

ll sought_nums_in_between(const ll a, const ll b) { return b - a + 1; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll a, b;
    cin >> a >> b;

    cout << sought_nums_in_between(a, b) << '\n';
    return 0;
}
