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

bool is_possible(const vi &xs, const int k) {
    if (k == 0) return true;

    for (int i = k + 1; i < sz(xs); ++i) {
        if (xs[i - 1] == xs[i]) continue;

        const int rest = sz(xs) - i;
        if (rest >= k) return true;
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
        int n, k;
        cin >> n >> k;

        vi xs(n);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        cout << (is_possible(xs, k) ? "YES" : "NO") << '\n';
    }

    return 0;
}
