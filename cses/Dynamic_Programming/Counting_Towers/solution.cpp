#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using mint = atcoder::modint1000000007;
static constexpr int LIM = 1'000'000;

// Encoding
//
// 0 |_._|   1 |_|_|   2 |.|.|
//
// 3 |_|.|   4 |.|_|   5 |...|

mint towers_num(const int h) { return -1; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << towers_num(n).val() << '\n';
    }

    return 0;
}
