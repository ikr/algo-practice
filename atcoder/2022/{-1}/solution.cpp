#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, X;
    cin >> N >> X;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    for (int i = 0; i < N; ++i) {
        if (X == xs[i]) {
            cout << (i + 1) << '\n';
        }
    }

    return 0;
}
