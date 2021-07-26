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

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

set<int> all_1_to_n(const int n) {
    vi xs(n);
    iota(begin(xs), end(xs), 1);
    return set<int>(cbegin(xs), cend(xs));
}

vi lower(const vi &xs) {
    auto av = all_1_to_n(sz(xs));
    av.erase(xs[0]);
    vi ans(sz(xs), xs[0]);

    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] != xs[i - 1]) {
            ans[i] = xs[i];
            av.erase(xs[i]);
        } else {
            ans[i] = *cbegin(av);
            av.erase(cbegin(av));
        }
    }

    return ans;
}

template <typename T>
T immediately_under(const set<T> &xs, const T &x, const T &when_missing) {
    auto it = xs.lower_bound(x);
    return it == xs.cbegin() ? when_missing : *(--it);
}

vi upper(const vi &xs) {
    auto av = all_1_to_n(sz(xs));
    av.erase(xs[0]);
    vi ans(sz(xs), xs[0]);

    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] != xs[i - 1]) {
            ans[i] = xs[i];
            av.erase(xs[i]);
        } else {
            ans[i] = immediately_under(av, xs[i], 0);
            av.erase(ans[i]);
        }
    }

    return ans;
}

pair<vi, vi> possible_range(const vi &xs) { return {lower(xs), upper(xs)}; }

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

        const auto [lo, hi] = possible_range(xs);
        cout << lo << '\n' << hi << '\n';
    }

    return 0;
}
