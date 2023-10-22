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
        if (A[i] == B[i] || (A[i] < B[i]) != (A[0] < B[0])) break;
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

template <typename T>
bool are_cross_palindromes(const vector<T> &xs, const vector<T> &ys) {
    const auto n = sz(xs);
    assert(sz(ys) == n);
    for (int i = 0; i < n / 2; ++i) {
        if (xs[i] != ys[n - 1 - i]) return false;
        if (ys[i] != xs[n - 1 - i]) return false;
    }
    return true;
}

optional<int> ops_to_meta(vector<int> A, vector<int> B) {
    const auto i0 = monotonic_pivot_index(A, B);
    if (!i0) return nullopt;

    const auto n = sz(A);
    if (*i0 == n / 2) {
        if (are_cross_palindromes(A, B)) return 0;
        return nullopt;
    }

    if (*i0 == n) {
        int result{};
        if (A[0] > B[0]) {
            ranges::reverse(A);
            ranges::reverse(B);
            swap(A, B);
            result += n;
        }

        const auto p = n / 2;
        vector<int> A_(cbegin(A) + p, cend(A));
        vector<int> B_(cbegin(B) + p, cend(B));

        reverse(begin(A), begin(A) + p);
        reverse(begin(B), begin(B) + p);

        A_.insert(cend(A_), cbegin(B), cbegin(B) + p);
        B_.insert(cend(B_), cbegin(A), cbegin(A) + p);

        if (!are_cross_palindromes(A_, B_)) return nullopt;
        result += n / 2;
        return result;
    }

    if (*i0 > n / 2) {
        const auto p = *i0 - n / 2;
        vector<int> A_(cbegin(A) + p, cend(A));
        vector<int> B_(cbegin(B) + p, cend(B));

        reverse(begin(A), begin(A) + p);
        reverse(begin(B), begin(B) + p);

        A_.insert(cend(A_), cbegin(B), cbegin(B) + p);
        B_.insert(cend(B_), cbegin(A), cbegin(A) + p);

        if (!are_cross_palindromes(A_, B_)) return nullopt;
        return p + (A[0] < B[0] ? 0 : n);
    }

    assert(*i0 < n / 2);
    if (i0 == 0) {
        assert(n % 2);
        const auto p = n / 2 + 1;
        vector<int> A_(cbegin(A) + p, cend(A));
        vector<int> B_(cbegin(B) + p, cend(B));

        reverse(begin(A), begin(A) + p);
        reverse(begin(B), begin(B) + p);

        A_.insert(cend(A_), cbegin(B), cbegin(B) + p);
        B_.insert(cend(B_), cbegin(A), cbegin(A) + p);

        if (!are_cross_palindromes(A_, B_)) return nullopt;
        return p + (A[0] < B[0] ? 0 : n);
    }
    {
        const auto p = n - 1 - *i0;
        vector<int> A_(cbegin(A) + p, cend(A));
        vector<int> B_(cbegin(B) + p, cend(B));

        reverse(begin(A), begin(A) + p);
        reverse(begin(B), begin(B) + p);

        A_.insert(cend(A_), cbegin(B), cbegin(B) + p);
        B_.insert(cend(B_), cbegin(A), cbegin(A) + p);

        if (!are_cross_palindromes(A_, B_)) return nullopt;
        return p + (A[0] < B[0] ? 0 : n);
    }
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
