#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

double solve(const int M, vector<int> A) {
    const auto N = sz(A);
    sort(begin(A), end(A));
    const auto tail = accumulate(crbegin(A), crbegin(A) + M - 1, 0);

    const auto head_size = N - M + 1;
    const auto m =
        (head_size % 2 ? doof(A[head_size / 2])
                       : (doof(A[head_size / 2 - 1] + A[head_size / 2]) / 2.0));

    return doof(tail) + m;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(7) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, M;
        cin >> N >> M;

        vector<int> A(N);
        for (auto &a : A) cin >> a;

        cout << "Case #" << i << ": " << solve(M, move(A)) << '\n';
    }

    return 0;
}
