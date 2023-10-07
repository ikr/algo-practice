#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

long double max_walk(const vector<long double> &xs) {
    const int N = sz(xs);

    if (N == 5) {
        return max((xs[3] + xs[4]) / 2.0 - (xs[2] + xs[0]) / 2.0,
                   (xs[2] + xs[4]) / 2.0 - (xs[0] + xs[1]) / 2.0);
    }

    return (xs[N - 2] + xs[N - 1]) / 2.0 - (xs[0] + xs[1]) / 2.0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << setprecision(7) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<long double> X(N);
        for (auto &x : X) cin >> x;
        ranges::sort(X);

        cout << "Case #" << i << ": " << max_walk(X) << '\n';
    }

    return 0;
}
