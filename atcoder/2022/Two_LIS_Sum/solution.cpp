#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

// https://github.com/kth-competitive-programming/kactl/blob/main/content/various/LIS.h
namespace kactl {
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
typedef vector<int> vi;

template <class I> vi lis(const vector<I> &S) {
    if (S.empty()) return {};
    vi prev(sz(S));
    typedef pair<I, int> p;
    vector<p> res;
    rep(i, 0, sz(S)) {
        // change 0 -> i for longest non-decreasing subsequence
        auto it = lower_bound(all(res), p{S[i], 0});
        if (it == res.end()) res.emplace_back(), it = res.end() - 1;
        *it = {S[i], i};
        prev[i] = it == res.begin() ? 0 : (it - 1)->second;
    }
    int L = sz(res), cur = res.back().second;
    vi ans(L);
    while (L--) ans[L] = cur, cur = prev[cur];
    return ans;
}
} // namespace kactl

static constexpr int N_MAX = 3 * 100'000;

int max_target(const vector<int> &A, const vector<int> &B) {
    const auto N = sz(A);
    vector<int> idx(N, 0);
    iota(begin(idx), end(idx), 0);

    sort(begin(idx), end(idx), [&](const int i, const int j) {
        return min(A[i], B[i]) < min(A[j], B[j]);
    });

    vector<int> A_(N, 0);
    vector<int> B_(N, 0);

    for (int i = 0; i < N; ++i) {
        A_[i] = A[idx[i]];
        B_[i] = B[idx[i]];
    }

    return sz(kactl::lis(A_)) + sz(kactl::lis(B_));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    vector<int> B(N);
    for (auto &b : B) cin >> b;

    cout << max_target(A, B) << '\n';
    return 0;
}
