#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll min_moves(const vi &xs) {
    if (sz(xs) == 2) return 0;
    if (sz(xs) == 3) return min(xs[1] - xs[0], xs[2] - xs[1]);

    const int a = xs[0];
    const int b = xs[1];
    const int c = xs[sz(xs) - 2];
    const int d = xs.back();

    return min(abs(llof(c) - a - llof(d - b)), abs(llof(d) - a - llof(c - b)));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        cout << min_moves(xs) << '\n';
    }

    return 0;
}
