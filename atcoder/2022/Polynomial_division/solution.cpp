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

vector<int> find_B(const vector<int> &A, const vector<int> &C) {
    const int N = sz(A) - 1;
    const int M = sz(C) - 1 - N;
    vector<int> B(M + 1, 0);

    assert(C[0] % A[0] == 0);
    B[0] = C[0] / A[0];

    for (int i = 1; i <= M; ++i) {
        const auto r = [&]() -> int {
            int result{};

            for (int j = 1; j <= i; ++j) {
                result += (j < sz(A) ? A[j] : 0) * B[i - j];
            }

            return result;
        }();

        assert((C[i] - r) % A[0] == 0);
        B[i] = (C[i] - r) / A[0];
    }

    return B;
}

vector<int> find_B_(const vector<int> &A, const vector<int> &C) {
    const int N = sz(A) - 1;
    const int M = sz(C) - 1 - N;
    vector<int> B(M + 1, 0);

    assert(C[N + M] % A[N] == 0);
    B[M] = C[N + M] / A[N];

    for (int i = M - 1; i >= 0; --i) {
        const int d = M - i;

        const auto r = [&]() -> int {
            int result{};

            for (int j = 1; j <= d; ++j) {
                result += (((N - d) < sz(A) && (N - d >= 0)) ? A[N - d] : 0) *
                          B[M - d];
            }

            return result;
        }();

        assert((C[N + M - d] - r) % A[N] == 0);
        B[i] = (C[N + M - d] - r) / A[N];
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

    cout << (!A[0] ? find_B(A, C) : find_B_(A, C)) << '\n';
    return 0;
}
