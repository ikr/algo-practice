#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

ostream &operator<<(ostream &os, const array<ll, 10> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

ostream &operator<<(ostream &os, const vector<array<ll, 10>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

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

vector<array<ll, 10>> counts_by_length(const int digits_num) {
    // tbl[i][j] is # of sought int-s having i digits, and starting with digit j
    vector<array<ll, 10>> tbl(digits_num + 1, array<ll, 10>{});
    tbl[1].fill(1);

    for (int i = 2; i <= digits_num; ++i) {
        const auto s = accumulate(cbegin(tbl[i - 1]), cend(tbl[i - 1]), 0LL);
        tbl[i][0] = s;
        for (int j = 1; j < 10; ++j) tbl[i][j] = s - tbl[i - 1][j];
    }

    return tbl;
}

ll sought_nums_up_to(const vi &ds, const vector<array<ll, 10>> &tbl) {
    const int n = sz(ds);
    assert(n > 0);
    ll ans = 0;

    cerr << ds << endl;

    for (int j = 0; j <= ds[0]; ++j) ans += tbl[n][j];

    for (int i = n - 1; i > 0; --i) {
        for (int j = ds[n - i]; j < 10; ++j) {
            ans -= tbl[i][j];
        }
    }

    return ans;
}

ll sought_nums_in_between(const ll a, const ll b) {
    const auto ds_b = digits(b);
    const auto tbl = counts_by_length(sz(ds_b));
    const auto nums_hi = sought_nums_up_to(ds_b, tbl);
    return a ? (nums_hi - sought_nums_up_to(digits(a - 1), tbl)) : nums_hi;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll a, b;
    cin >> a >> b;

    cout << sought_nums_in_between(a, b) << '\n';
    return 0;
}
