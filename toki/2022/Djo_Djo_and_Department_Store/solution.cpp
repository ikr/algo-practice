#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll diff_of_paid_totals(const vector<int> &A, const int X,
                       const vector<int> &B) {
    const auto N = sz(A);

    const auto Djowen = [&]() -> ll {
        priority_queue<int, vector<int>, greater<int>> q;
        int from_A{};
        ll result{};

        for (int i = 0; i < N; ++i) {
            if (A[i] >= B[i]) {
                result += A[i];
                ++from_A;
            } else {
                result += B[i];
                q.push(B[i] - A[i]);
            }
        }

        while (from_A < X) {
            const auto x = q.top();
            q.pop();
            result -= x;
            ++from_A;
        }

        return result;
    }();

    const auto Djonatan = [&]() -> ll {
        priority_queue<int> q;
        int from_A{};
        ll result{};

        for (int i = 0; i < N; ++i) {
            if (A[i] <= B[i]) {
                result += A[i];
                ++from_A;
            } else {
                result += B[i];
                q.push(B[i] - A[i]);
            }
        }

        while (from_A < X) {
            const auto x = q.top();
            q.pop();

            result -= x;
            ++from_A;
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

    cout << diff_of_paid_totals(A, X, B) << '\n';
    return 0;
}
