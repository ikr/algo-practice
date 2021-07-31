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

static constexpr int INF = 1e9 + 7;

int min_diff(const vi &xs, const vi &ys) {
    int ans = INF;

    for (const auto x : xs) {
        auto it = lower_bound(cbegin(ys), cend(ys), x);
        if (it == cend(ys)) {
            it = prev(it);
        }

        const auto jt = (it == cbegin(ys)) ? it : prev(it);

        ans = min({ans, abs(*it - x), abs(*jt - x)});
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n, m;
    cin >> n >> m;

    vi xs(n);
    for (auto &x : xs) cin >> x;

    vi ys(m);
    for (auto &y : ys) cin >> y;
    sort(begin(ys), end(ys));

    cout << min_diff(xs, ys) << '\n';
    return 0;
}
