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

map<ll, int> even_counts(const vll &xs) {
    map<ll, int> cs;
    for (const auto x : xs) ++cs[x];

    for (auto it = begin(cs); it != end(cs);) {
        if (it->second % 2) {
            it->second--;
            if (!it->second) {
                it = cs.erase(it);
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }

    return cs;
}

bool good_workout(const ll r, const vll &xs, const ll w) {
    if (r >= w) return true;

    const auto cs = even_counts(xs);
    ll total = r;

    for (auto it = crbegin(cs); it != crend(cs); ++it) {
        const auto x = it->first;
        const auto mul = it->second;
        total += x * mul;

        if (total >= w) return true;
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n, w, r;
        cin >> n >> w >> r;

        vll xs(n);
        for (auto &x : xs) cin >> x;

        cout << (good_workout(r, xs, w) ? "YES\n" : "NO\n");
    }

    return 0;
}
