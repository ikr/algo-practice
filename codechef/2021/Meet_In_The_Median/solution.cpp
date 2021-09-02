#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

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
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

pair<int, vi> solve(const vi &xs, const int K) {
    vi idx(sz(xs));
    iota(begin(idx), end(idx), 0);
    sort(begin(idx), end(idx),
         [&](const int i, const int j) { return xs[i] > xs[j]; });

    set<int> ys;
    for (int i = 0; i < K; ++i) {
        ys.insert(idx[i]);
    }

    vi ans;
    ans.reserve(K);
    for (const auto i : ys) {
        ans.push_back(xs[i]);
    }

    return {xs[idx[K / 2]], ans};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int N, K;
        cin >> N >> K;

        vi xs(N);
        for (auto &x : xs) cin >> x;

        const auto [m, ys] = solve(xs, K);
        cout << m << '\n' << ys << '\n';
    }

    return 0;
}
