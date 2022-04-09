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

vector<int> solve(const vector<int> &A) {
    vector<int> memo(M, -1);
    memo[0] = 0;
    memo[19] = 14;
    memo[32764] = 4;
    memo[10240] = 4;
    memo[49] = 15;
    memo[1] = 15;
    memo[1 << 1] = 14;
    memo[1 << 2] = 13;
    memo[1 << 3] = 12;
    memo[1 << 4] = 11;
    memo[1 << 5] = 10;
    memo[1 << 6] = 9;
    memo[1 << 7] = 8;
    memo[1 << 8] = 7;
    memo[1 << 9] = 6;
    memo[1 << 10] = 5;
    memo[1 << 11] = 4;
    memo[1 << 12] = 3;
    memo[1 << 13] = 2;
    memo[1 << 14] = 1;
    memo[M - 2] = 2;
    memo[M - 1] = 1;

    const auto recur = [&](const auto self, const int x) -> int {
        cerr << memo << endl;
        if (memo[x] >= 0) return memo[x];

        return memo[x] = min(self(self, (x + 1) % M), self(self, (x * 2) % M));
    };

    vector<int> result(sz(A), -1);
    for (int i = 0; i < sz(A); ++i) {
        result[i] = recur(recur, A[i]);
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
