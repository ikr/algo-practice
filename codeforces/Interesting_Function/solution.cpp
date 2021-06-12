#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi digits_reversed(int x) {
    if (!x) return {0};

    vi ans;
    while (x) {
        ans.push_back(x % 10);
        x /= 10;
    }
    return ans;
}

ll n_ones(const int n) {
    assert(n > 0);
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ans *= 10;
        ++ans;
    }
    return ans;
}

ll changes_num_from_zero(const int x) {
    const auto ds = digits_reversed(x);
    ll ans = 0;

    for (int i = 0; i < sz(ds); ++i) {
        ans += n_ones(i + 1) * ds[i];
    }

    return ans;
}

ll changes_num(const int lo, const int hi) {
    return changes_num_from_zero(hi) - changes_num_from_zero(lo);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int lo, hi;
        cin >> lo >> hi;

        cout << changes_num(lo, hi) << '\n';
    }

    return 0;
}
