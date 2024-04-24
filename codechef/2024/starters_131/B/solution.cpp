#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const multiset<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll opt_diff(vector<ll> A, const ll K) {
    const auto T = A.back();
    for (int i = 0; i < sz(A); ++i) {
        const ll q = (T - A[i]) / K;
        const auto a = A[i] + q * K;
        A[i] = a;
    }

    multiset<ll> xs(cbegin(A), cend(A));
    ll result = *crbegin(xs) - *cbegin(xs);

    for (int i = 0; i < sz(A); ++i) {
        const auto x = *cbegin(xs);
        xs.erase(cbegin(xs));
        xs.insert(x + K);
        const ll result_ = *crbegin(xs) - *cbegin(xs);
        result = min(result, result_);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N, K;
        cin >> N >> K;

        vector<ll> A(N);
        for (auto &a : A) cin >> a;
        sort(begin(A), end(A));
        cout << opt_diff(std::move(A), K) << '\n';
    }

    return 0;
}
