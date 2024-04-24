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

ll opt_diff(const vector<ll> &A, const ll K) {
    multiset<ll> xs(cbegin(A), cend(A));
    ll result = *crbegin(xs) - *cbegin(xs);

    for (;;) {
        const auto x = *cbegin(xs);
        xs.erase(cbegin(xs));
        xs.insert(x + K);
        cerr << xs << endl;
        const ll result_ = *crbegin(xs) - *cbegin(xs);
        if (result_ > result) break;
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
        cout << opt_diff(A, K) << '\n';
    }

    return 0;
}
