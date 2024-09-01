#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint1000000007;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<int, int> gather_freqs(const vector<int> &xs) {
    map<int, int> result;
    for (const auto x : xs) ++result[x];
    return result;
}

mint expected(const vector<int> &xs) {
    mint p{0};
    for (const auto x : xs) {
        p += x;
    }

    const mint q{sz(xs)};
    return p * q.inv();
}

mint expected_without(const vector<int> &xs, const int x0) {
    mint p{0};
    for (const auto x : xs) {
        p += x;
    }
    p -= x0;

    const mint q{sz(xs)};
    return p * q.inv();
}

mint expected_prod(const vector<int> &xs) {
    const auto n = sz(xs);

    mint p0{0};
    for (const auto x : xs) {
        p0 += x;
    }
    const mint q0{n};

    mint s{0};
    const mint q1{n - 1};
    for (const auto x : xs) {
        const mint p1 = p0 - x;
        s += x * p1 * q1.inv();
    }

    return s * q0.inv();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << expected_prod(xs).val() << '\n';
    }

    return 0;
}
