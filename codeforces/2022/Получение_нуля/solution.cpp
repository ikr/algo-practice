#include <algorithm>
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

vector<int> solve(vector<int> A) {
    vector<int> memo(M, 15);
    memo[0] = 0;

    for (int x = 1; x < M; ++x) {
        for (int i = 0; i < 15; ++i) {
            int p = 0;
            while (((x + i) << p) % M != 0) ++p;
            memo[x] = min(memo[x], i + p);
        }
    }

    transform(cbegin(A), cend(A), begin(A),
              [&memo](const int a) { return memo[a]; });
    return A;
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

    cout << solve(move(A)) << '\n';
    return 0;
}
