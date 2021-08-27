#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint1000000007;

bool is_possible_upper_row(const int n, const int bits) {
    int span = (bits & 1) ? 1 : 0;
    for (int shift = 1; shift < n; ++shift) {
        if ((1 << shift) & bits) {
            ++span;
        } else {
            if (span % 2) return false;
            span = 0;
        }
    }

    return span % 2 == 0;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int num_ways(const int n, const int m) {
    assert(is_possible_upper_row(10, 0));
    assert(is_possible_upper_row(10, 3));
    assert(!is_possible_upper_row(10, 7));
    assert(!is_possible_upper_row(10, 5));
    assert(is_possible_upper_row(10, 6));
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;
    cout << num_ways(n, m) << '\n';
    return 0;
}
