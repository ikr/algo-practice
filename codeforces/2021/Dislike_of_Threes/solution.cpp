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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    vi xs;
    xs.reserve(1000);

    for (int x = 1;; ++x) {
        if (x % 10 == 3 || x % 3 == 0) continue;
        xs.push_back(x);
        if (sz(xs) >= 1000) break;
    }

    int t;
    cin >> t;
    while (t--) {
        int k;
        cin >> k;
        cout << xs[k - 1] << '\n';
    }

    return 0;
}
