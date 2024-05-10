#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k, Q;
        cin >> n >> k >> Q;

        vector<int> A(k);
        for (auto &a : A) cin >> a;
        A.insert(cbegin(A), 0);

        vector<int> B(k);
        for (auto &b : B) cin >> b;
        B.insert(cbegin(B), 0);

        vector<ll> result;
        result.reserve(Q);

        for (int q = 1; q <= Q; ++q) {
            int d;
            cin >> d;

            const auto it = lower_bound(cbegin(A), cend(A), d);
            assert(it != cend(A));
            if (*it == d) {
                const auto i = inof(it - cbegin(A));
                result.push_back(B[i]);
            } else {
                const auto jt = prev(lower_bound(cbegin(A), cend(A), d));
                const auto i = inof(jt - cbegin(A));

                const ll s0 = A[i];
                assert(i + 1 < sz(A));
                const ll s1 = A[i + 1];
                const ll dt01 = B[i + 1] - B[i];

                result.push_back(B[i] + dt01 * (d - s0) / (s1 - s0));
            }
        }
        cout << result << '\n';
    }

    return 0;
}
