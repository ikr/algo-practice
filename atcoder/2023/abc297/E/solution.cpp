#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
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

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll kth_lowest(const vector<ll> &A, const int K) {
    const auto N = sz(A);
    set<ll> basis;
    for (int bits = 1; bits < (1 << N); ++bits) {
        ll s{};
        for (int i = 0; i < N; ++i) {
            if ((1 << i) & bits) {
                s += A[i];
            }
        }

        basis.insert(s);
    }

    const vector<ll> bs(cbegin(basis), cend(basis));
    set<ll> all{bs[0]};
    for (int i = 1; i < sz(bs); ++i) {
        const auto hi = bs[i];

        for (int j = 0; j < i; ++j) {
            ll m = 2;
            while (sz(all) < K && bs[j] * m < hi) {
                all.insert(bs[j] * m);
                ++m;
            }
        }

        all.insert(hi);
        while (sz(all) > K) {
            all.erase(prev(cend(all)));
        }
    }

    cerr << all << endl;
    return *crbegin(all);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, K;
    cin >> N >> K;

    vector<ll> A(N);
    for (auto &a : A) cin >> a;
    sort(begin(A), end(A));
    A.erase(unique(begin(A), end(A)), end(A));

    cout << kth_lowest(A, K) << '\n';
    return 0;
}
