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

int trailing_ones_num(const int x) {
    assert(0 <= x && x < M);
    int i = 0;
    while (i < 15 && (1 << i) & x) {
        ++i;
    }
    return i;
}

int trailing_zeros_num(const int x) {
    assert(0 <= x && x < M);
    int i = 0;
    while (i < 15 && !((1 << i) & x)) {
        ++i;
    }
    return i;
}

int min_ops(const int x) {
    if (!x) return 0;
    const auto tos = trailing_ones_num(x);
    if (tos > 1) {
        return min(1 + 15 - tos, M - x);
    }

    const int tzs = trailing_zeros_num(x);
    return min(15 - tzs, M - x);
}

vector<int> solve(const vector<int> &A) {
    vector<int> result(sz(A), -1);
    for (int i = 0; i < sz(A); ++i) {
        result[i] = min_ops(A[i]);
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
