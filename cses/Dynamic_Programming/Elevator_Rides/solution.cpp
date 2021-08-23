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
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vll subset_weights(const vi &xs) {
    const auto lim = 1 << sz(xs);
    vll ans(lim, 0);

    for (int bits = 1; bits < lim; ++bits) {
        for (int i = 0; i < sz(xs); ++i) {
            if ((1 << i) & bits) {
                ans[bits] += xs[i];
            }
        }
    }

    return ans;
}

int min_rides(const int cap, const vi &xs) {
    cerr << subset_weights(xs) << endl;
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, cap;
    cin >> n >> cap;

    vi xs(n);
    for (auto &x : xs) cin >> x;

    cout << min_rides(cap, xs) << '\n';
    return 0;
}
