#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll diff_of_paid_totals(vector<int> A, const int X, vector<int> B) {
    const auto Djowen = [&]() -> ll {
        vector<int> idx(sz(A));
        iota(begin(idx), end(idx), 0);

        sort(begin(idx), end(idx), [&](const int i, const int j) {
            if (A[i] == A[j]) return B[i] < B[j];
            return A[i] > A[j];
        });

        ll result{};

        for (int i = 0; i < X; ++i) {
            result += A[idx[i]];
        }

        for (int i = X; i < sz(A); ++i) {
            result += max(A[idx[i]], B[idx[i]]);
        }

        return result;
    }();

    const auto Djonatan = [&]() -> ll {
        vector<int> idx(sz(A));
        iota(begin(idx), end(idx), 0);

        sort(begin(idx), end(idx), [&](const int i, const int j) {
            if (A[i] == A[j]) return B[i] > B[j];
            return A[i] < A[j];
        });

        ll result{};

        for (int i = 0; i < X; ++i) {
            result += A[idx[i]];
        }

        for (int i = X; i < sz(A); ++i) {
            result += min(A[idx[i]], B[idx[i]]);
        }

        return result;
    }();

    return Djowen - Djonatan;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, X;
    cin >> N >> X;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    vector<int> B(N);
    for (auto &b : B) cin >> b;

    cout << diff_of_paid_totals(move(A), X, move(B)) << '\n';
    return 0;
}
