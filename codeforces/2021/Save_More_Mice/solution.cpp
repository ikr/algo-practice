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

int max_saved(const int n, const vi &xs) {
    int ans = 0;

    for (int i = sz(xs) - 1, t = 0; i >= 0; --i) {
        if (t >= xs[i]) break;
        const int run_time = n - xs[i];
        t += run_time;
        ++ans;
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
        int n, k;
        cin >> n >> k;

        vi xs(k);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        cout << max_saved(n, xs) << '\n';
    }

    return 0;
}
