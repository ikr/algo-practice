#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int ops_to_match(const int N, const int D, const int a, const int b) {
    if (a == b) return 0;

    for (int i = 1; i <= N * N; ++i) {
        const auto y = (a + i * D) % N;
        if (y == b) return i;

        const auto z = (((a - i * D) % N) + N) % N;
        if (z == b) return i;
    }

    return -1;
}

int solve(const vector<int> &X, const int N, const int D) {
    int ans{};
    int l = 0, r = sz(X) - 1;
    while (l != r) {
        const auto o =
            min(ops_to_match(N, D, X[l], X[r]), ops_to_match(N, D, X[r], X[l]));
        if (o < 0) return -1;
        ans += o;
        ++l;
        --r;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int W, N, D;
        cin >> W >> N >> D;

        vector<int> X(W);
        for (auto &x : X) {
            cin >> x;
            --x;
        }

        const auto ans = solve(X, N, D);
        cout << "Case #" << i << ": "
             << (ans >= 0 ? to_string(ans) : string{"IMPOSSIBLE"}) << '\n';
    }

    return 0;
}
