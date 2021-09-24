#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
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

struct State final {
    bool first_is_zero;
    int i;
    bool capped;
    int prev_digit;
};

bool operator<(const State &lhs, const State &rhs) {
    const array<int, 4> a{lhs.first_is_zero, lhs.i, lhs.capped, lhs.prev_digit};
    const array<int, 4> b{rhs.first_is_zero, rhs.i, rhs.capped, rhs.prev_digit};
    return a < b;
}

// The state, aka “what matters at this point”
//
// - Left-to-right index of the digit we're “standing” at
// - The digit we put now at this index
// - Do we have leading zeros up to to but not including this index?
// - Can we go up to 9 at the current index, or are we capped by the
//   digit in the number?

ll sought_nums_up_to(const ll hi) {
    const auto ds = digits(hi);
    const int n = sz(ds);
    assert(n > 0);

    vector<array<ll, 10>> DZ(n, array<ll, 10>{});
    vector<array<ll, 10>> DA(n, array<ll, 10>{});

    DZ[0][0] = 1;

    for (int j = 1; j <= ds[0]; ++j) {
        DA[0][j] = 1;
    }

    for (int i = 1; i < n; ++i) {
    }

    return accumulate(cbegin(DZ.back()), cend(DZ.back()), 0LL) +
           accumulate(cbegin(DA.back()), cend(DA.back()), 0LL);
}

ll sought_nums_in_between(const ll a, const ll b) {
    const auto nums_hi = sought_nums_up_to(b);
    return a ? (nums_hi - sought_nums_up_to(a - 1)) : nums_hi;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll a, b;
    cin >> a >> b;

    cout << sought_nums_in_between(a, b) << '\n';
    return 0;
}
