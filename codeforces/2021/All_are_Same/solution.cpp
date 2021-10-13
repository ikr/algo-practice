#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi uniques(const vi &xs) {
    const set<int> xss(cbegin(xs), cend(xs));
    return vi(cbegin(xss), cend(xss));
}

vi diffs(vi xs) {
    adjacent_difference(cbegin(xs), cend(xs), begin(xs));
    return vi(next(cbegin(xs)), cend(xs));
}

int max_possible_k(const vi &xs) {
    const auto us = uniques(xs);
    if (sz(us) == 1) return -1;

    const auto ds = diffs(us);
    return accumulate(next(cbegin(ds)), cend(ds), ds[0],
                      [](const int agg, const int x) { return gcd(agg, x); });
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;

        cout << max_possible_k(xs) << '\n';
    }

    return 0;
}
