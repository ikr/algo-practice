#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<int> &A, const int K) {
    const auto n = sz(A);
    if (n == 1 || K == 1) return true;
    vector<int> xs;

    for (int i = 0; i <= (n - 1) / 2; ++i) {
        const int j = n - 1 - i;
        if (A[i] != A[j]) xs.push_back(abs(A[i] - A[j]));
    }

    if (xs.empty()) return true;
    sort(begin(xs), end(xs));

    priority_queue<int, vector<int>, greater<int>> cuts;
    while (!xs.empty() || !cuts.empty()) {
        while (!cuts.empty() && (xs.empty() || cuts.top() >= xs.back())) {
            const auto x = cuts.top();
            cuts.pop();
            xs.push_back(x);
        }

        if (sz(xs) < K) return false;
        const auto p = xs[sz(xs) - K];

        for (int i = sz(xs) - K; i < sz(xs); ++i) {
            const auto y = xs[i] - p;
            if (y == 0) continue;
        }
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N, K;
        cin >> N >> K;

        vector<int> A(N);
        for (auto &a : A) cin >> a;

        cout << (is_possible(A, K) ? "YES" : "NO") << '\n';
    }

    return 0;
}
