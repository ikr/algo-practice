#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <optional>
#include <vector>
using namespace std;
using ll = long long;
using vi = vector<int>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

optional<vi> alans_subset(const int N, const ll X, const ll Y) {
    const ll T = llof(N) * llof(N + 1) / 2LL;
    const ll P = X * T;
    const ll Q = X + Y;
    if (P % Q != 0LL) return nullopt;
    const ll S = P / Q;

    if (S <= N) return vi{inof(S)};

    vi xs(N);
    iota(begin(xs), end(xs), 1);

    int lo = 0;
    int hi = sz(xs) - 1;
    ll s = T;
    if (s < S) return nullopt;

    while (hi - lo > 1) {
        if (s - xs[hi] >= S) {
            s -= xs[hi];
            --hi;
        } else if (s - xs[lo] >= S) {
            s -= xs[lo];
            ++lo;
        } else {
            return nullopt;
        }

        if (s == S) break;
    }

    return vi(cbegin(xs) + lo, cbegin(xs) + hi + 1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, X, Y;
        cin >> N >> X >> Y;

        const auto ans = alans_subset(N, X, Y);
        cout << "Case #" << i << ": " << (ans ? "POSSIBLE" : "IMPOSSIBLE")
             << '\n';
        if (ans) cout << sz(*ans) << '\n' << *ans << '\n';
    }

    return 0;
}
