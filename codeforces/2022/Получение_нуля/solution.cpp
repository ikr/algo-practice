#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

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

static constexpr int M = 32768;
static constexpr int INF = 1'000'000'000;

vector<int> solve(const vector<int> &A) {
    vector<int> memo(M, INF);
    memo[0] = 0;
    memo[M - 1] = 1;
    for (int i = 0; i < 15; ++i) {
        memo[1 << i] = 15 - i;
    }

    for (int x = 1; x < M; ++x) {
        memo[(x + 1) % M] = min(memo[(x + 1) % M], memo[x] + 1);
        memo[(x * 2) % M] = min(memo[(x * 2) % M], memo[x] + 1);
    }

    vector<int> result(sz(A), -1);
    for (int i = 0; i < sz(A); ++i) {
        result[i] = memo[A[i]];
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> A(n);
    for (auto &a : A) {
        cin >> a;
    }

    cout << solve(A) << '\n';
    return 0;
}
