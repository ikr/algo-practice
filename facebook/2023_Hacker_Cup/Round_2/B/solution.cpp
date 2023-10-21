#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

static const function<bool(int, int)> mless = less<int>{};
static const function<bool(int, int)> mgreater = greater<int>{};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool confirm_for_range(const vector<int> &A, const vector<int> &B,
                       const pii &lr, const function<bool(int, int)> &pred) {
    for (int i = lr.first; i <= min(lr.second, sz(A) - 1); ++i) {
        if (!pred(A[i], B[i])) return false;
    }
    return true;
}

optional<int> monotonic_pivot_index(const vector<int> &A,
                                    const vector<int> &B) {
    const auto n = sz(A);

    if (A[0] == B[0]) {
        if (n % 2 == 0) return nullopt;
        const auto pred = (A[1] < B[1]) ? mless : mgreater;
        if (confirm_for_range(A, B, {2, n - 1}, pred)) return 0;
    }

    int i = 1;
    for (; i < n; ++i) {
        if ((A[i] < B[i]) != (A[0] < B[0])) break;
    }

    if (i == n) {
        if (n % 2) return nullopt;
        return n;
    }

    if ((n % 2) && A[i] != B[i]) return nullopt;
    const auto pred = (A[0] < B[0]) ? mgreater : mless;
    if (confirm_for_range(A, B, {i + 1, n - 1}, pred)) {
        return i;
    } else {
        return nullopt;
    }
}

optional<int> ops_to_meta(vector<int> A, vector<int> B) {
    const auto i0 = monotonic_pivot_index(A, B);
    if (!i0) return nullopt;
    return nullopt;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;

        vector<int> A(n);
        for (auto &a : A) cin >> a;

        vector<int> B(n);
        for (auto &b : B) cin >> b;

        const auto x = ops_to_meta(A, B);
        cout << "Case #" << i << ": " << (x ? *x : -1) << '\n';
    }

    return 0;
}
