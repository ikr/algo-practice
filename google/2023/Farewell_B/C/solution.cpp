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

    for (int i = 0; i < N; ++i) {
        {
            cerr << "a:" << A[i].first << endl;
            const auto lo = A[i].first - K + 1;
            const auto it =
                lower_bound(cbegin(A), cbegin(A) + i, pii{lo, INT_MIN});
            if (it != cbegin(A) + i && it != cbegin(A)) {
                const auto d = inof(distance(cbegin(A), prev(it))) + 1;
                cerr << "+" << d << endl;
                ans[A[i].second] += d;
            }
        }
        {
            const auto hi = A[i].first + K;
            const auto it =
                lower_bound(cbegin(A) + i + 1, cend(A), pii{hi, INT_MIN});
            if (it != cend(A)) {
                const auto d = inof(distance(it, cend(A)));
                cerr << "+" << d << endl;
                ans[A[i].second] += d;
            }
        }
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
