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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll closest_to_b(const vector<ll> &A, const ll b) {
    const auto it = lower_bound(cbegin(A), cend(A), b);
    const auto lo = it == cbegin(A) ? *it : *prev(it);
    const auto hi = it == cend(A) ? A.back() : *it;
    return abs(lo - b) <= abs(hi - b) ? lo : hi;
}

ll min_ops(const vector<ll> &A, const vector<ll> &B) {
    const auto sa = accumulate(cbegin(A), cend(A), 0LL);
    const auto sb = accumulate(cbegin(B), cend(B), 0LL);

    ll result{LONG_LONG_MAX};
    for (const auto b : B) {
        result =
            min(result, abs(sa - sb + b) + abs(b - closest_to_b(A, b)) + 1);
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<ll> A(n);
        for (auto &a : A) cin >> a;
        sort(begin(A), end(A));
        cerr << A << endl;

        vector<ll> B(n + 1);
        for (auto &b : B) cin >> b;
        sort(begin(B), end(B));
        cerr << B << endl << endl;

        cout << min_ops(A, B) << '\n';
    }

    return 0;
}
