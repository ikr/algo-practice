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

template <typename T> vi digits_reversed(T n) {
    vi ans;

    while (n) {
        ans.push_back(inof(n % static_cast<T>(10)));
        n /= static_cast<T>(10);
    }

    return ans;
}

template <typename T> vi digits(T n) {
    vi ans = digits_reversed(n);
    reverse(begin(ans), end(ans));
    return ans;
}

optional<int> last_index_of(const vi &xs, const int a, const int hi) {
    for (int i = hi - 1; i >= 0; --i) {
        if (xs[i] == a) return i;
    }

    return nullopt;
}

optional<pii> last_indices_of(const vi &xs, const int a, const int b) {
    const auto pj = last_index_of(xs, b, sz(xs));
    if (!pj) return nullopt;

    const auto pi = last_index_of(xs, a, *pj);
    if (!pi) return nullopt;

    return pii{*pi, *pj};
}

int min_steps(const ll n) {
    const auto ds = digits(n);
    const vector<pii> patterns{{0, 0}, {2, 5}, {5, 0}, {7, 5}};

    int ans = INT_MAX;

    for (const auto [a, b] : patterns) {
        const auto ij = last_indices_of(ds, a, b);
        if (!ij) continue;

        const auto [i, j] = *ij;
        assert(i < j);
        ans = min(ans, j - i - 1 + sz(ds) - 1 - j);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;

        cout << min_steps(n) << '\n';
    }

    return 0;
}
