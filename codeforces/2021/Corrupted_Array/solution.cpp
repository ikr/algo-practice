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

vll solution(const vll &xs) {
    ll s = accumulate(cbegin(xs), prev(prev(cend(xs))), 0LL);
    if (s == xs.back() || s == xs[sz(xs) - 2]) {
        return vll(cbegin(xs), prev(prev(cend(xs))));
    }

    s += xs[sz(xs) - 2];
    vll ans(cbegin(xs), prev(cend(xs)));

    for (auto it = cbegin(ans); it != cend(ans); ++it) {
        if (s - *it == xs.back()) {
            ans.erase(it);
            return ans;
        }
    }

    return {};
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

        vll xs(n + 2);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        const auto ans = solution(xs);
        if (ans.empty()) {
            cout << "-1\n";
        } else {
            cout << ans << '\n';
        }
    }

    return 0;
}
