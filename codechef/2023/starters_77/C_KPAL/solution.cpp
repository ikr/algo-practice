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

bool is_possible(const vector<int> &A, const ll K) {
    const auto n = sz(A);
    if (n == 1 || K == 1) return true;
    vector<int> xs;
    xs.reserve(n / 2);

    for (int i = 0; i <= (n - 1) / 2; ++i) {
        const int j = n - 1 - i;
        xs.push_back(abs(A[i] - A[j]));
    }

    const auto s = accumulate(cbegin(xs), cend(xs), 0LL, plus<ll>{});
    return (s % K) == 0LL;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N, K;
        cin >> N >> K;

        vector<int> A(N);
        for (auto &a : A) cin >> a;

        cout << (is_possible(A, K) ? "YES" : "NO") << '\n';
    }

    return 0;
}
