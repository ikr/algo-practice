#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

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

vll counts_by_length(const int digits_num) {
    // tbl[i] is # of sought Inst having i digits, starting with a fixed digit
    // (no matter which one)
    vll tbl(digits_num + 1, 0);
    tbl[1] = 1;
    for (int i = 2; i < sz(tbl); ++i) tbl[i] = 9 * tbl[i - 1];
    return tbl;
}

ll sought_nums_up_to(const ll hi) {
    const auto ds = digits(hi);
    const auto tbl = counts_by_length(sz(ds));

    ll ans = tbl[sz(ds), ds[0]] * ds[0];

    for (int i = 1; i < sz(ds); ++i) {
        ans -= tbl[sz(ds) - i] * (10 - ds[i]);
    }

    return ans;
}

ll sought_nums_in_between(const ll a, const ll b) {
    return a ? (sought_nums_up_to(b) - sought_nums_up_to(a - 1))
             : sought_nums_up_to(b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll a, b;
    cin >> a >> b;

    cout << sought_nums_in_between(a, b) << '\n';
    return 0;
}
