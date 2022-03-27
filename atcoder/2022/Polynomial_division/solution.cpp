#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

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

template <typename T> constexpr T safe_get(const vector<T> &xs, const int i) {
    return (0 <= i && i < sz(xs)) ? xs[i] : 0;
}

vector<int> find_B(const vector<int> &A, const vector<int> &C) {
    const int N = sz(A) - 1;
    const int M = sz(C) - 1 - N;
    vector<int> B(M + 1, 0);

    for (int d = 0; d <= M; ++d) {
        const auto r = [&]() -> int {
            int result{};

            for (int q = 1; q <= d; ++q) {
                const int ia = N - q;
                const int ib = (N + M - d) - ia;
                result += safe_get(A, ia) * safe_get(B, ib);
            }

            return result;
        }();

        assert((C[N + M - d] - r) % A[N] == 0);
        B[M - d] = (C[N + M - d] - r) / A[N];
    }

    return B;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<int> A(N + 1, 0);
    for (auto &a : A) cin >> a;

    vector<int> C(N + M + 1, 0);
    for (auto &c : C) cin >> c;

    cout << find_B(A, C) << '\n';
    return 0;
}
