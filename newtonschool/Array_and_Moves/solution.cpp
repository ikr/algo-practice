#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

static constexpr ll INF = 1e18;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll brute_force(const vector<ll> xs, const ll K) {
    ll result = INF;

    for (int i = 0; i < sz(xs) - 1; ++i) {
        for (int j = i + 1; j < sz(xs); ++j) {
            const auto t = accumulate(cbegin(xs) + i, cbegin(xs) + j, 0LL);
            result = min(result, abs(t - K));
        }
    }

    return result;
}

ll min_ops(const vector<ll> xs, const ll K) {
    const auto delta = [K](const ll x) { return abs(K - x); };

    set<ll> prefix_sums{xs[0]};
    ll cur = xs[0];
    ll result = delta(xs[0]);

    for (int i = 1; i < sz(xs); ++i) {
        cur += xs[i];
        result = min(result, delta(cur));

        auto it = prefix_sums.lower_bound(cur - K);
        const auto jt = (it == cbegin(prefix_sums) ? it : prev(it));
        if (it == cend(prefix_sums)) it = jt;

        result = min(result, delta(cur - *it));
        result = min(result, delta(cur - *jt));
        prefix_sums.insert(cur);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, K;
    cin >> N >> K;

    vector<ll> xs(N);
    for (auto &x : xs) cin >> x;

    // if (brute_force(xs, K) != min_ops(xs, K)) {
    //     cerr << "actual:" << min_ops(xs, K)
    //          << " expected:" << brute_force(xs, K) << endl;
    // }

    cout << min_ops(xs, K) << '\n';
    return 0;
}
