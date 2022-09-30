#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

int max_hits(vector<ll> xs, vector<ll> ys) {
    sort(begin(xs), end(xs));
    sort(begin(ys), end(ys));

    set<int> ds;
    for (const auto x : xs) {
        for (const auto y : ys) {
            ds.insert(x - y);
        }
    }

    int result{};

    for (int i = 0; i < sz(xs); ++i) {
        const auto d = xs[i] - ys[0];
        int cur = 1;

        for (int j = 1; j < sz(ys) && i + j < sz(xs); ++j) {
            cur += binary_search(xbegin(xs) + i + j, xend(xs), ys[j] + d);
        }

        result = max(result, cur);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<ll> xs(N);
    for (auto &x : xs) cin >> x;

    vector<ll> ys(M);
    for (auto &y : ys) cin >> y;

    cout << max_hits(move(xs), move(ys)) << '\n';
    return 0;
}
