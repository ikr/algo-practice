#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> solve(const vector<pii> &A, const int K) {
    const auto N = sz(A);
    vector<int> ans(N, 1);

    vector<int> lhs(N, 0);
    for (int i = 0; i < N; ++i) {
        const auto lo = A[i].first - K + 1;
        const auto it = lower_bound(cbegin(A), cbegin(A) + i, pii{lo, INT_MIN});
        if (it != cbegin(A)) {
            const auto j = inof(distance(cbegin(A), prev(it)));
            lhs[i] = lhs[j] + 1;
        }
    }

    vector<int> rhs(N, 0);
    for (int i = N - 1; i >= 0; --i) {
        const auto hi = A[i].first + K;
        const auto it =
            lower_bound(cbegin(A) + i + 1, cend(A), pii{hi, INT_MIN});
        if (it != cend(A)) {
            const auto j = distance(cbegin(A), it);
            rhs[i] = rhs[j] + 1;
        }
    }

    for (int i = 0; i < N; ++i) {
        ans[A[i].second] += lhs[i] + rhs[i];
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, K;
        cin >> N >> K;

        vector<pii> A(N);
        for (int j = 0; j < N; ++j) {
            int a;
            cin >> a;
            A[j] = pii{a, j};
        }

        sort(begin(A), end(A));

        cout << "Case #" << i << ": " << solve(A, K) << '\n';
    }

    return 0;
}
