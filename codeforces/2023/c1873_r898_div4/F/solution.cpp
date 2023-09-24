#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_interesting_length(const vector<int> &A, const vector<int> &H,
                           const int K) {
    vector<int> ss(sz(A) + 1, 0);
    partial_sum(cbegin(A), cend(A), begin(ss) + 1);

    const auto is_possible = [&](const int interval_size) -> bool {
        for (int l{}, r{};;) {
            assert(l <= r);
            if (l == sz(A) - 1) break;

            while (r + 1 <= sz(A) - 1 && (H[r] % (long long)H[r + 1]) == 0LL &&
                   ss[r + 2] - ss[l] <= K) {
                ++r;
                if (r - l + 1 == interval_size) return true;
            }

            if (r == l) {
                ++l;
                ++r;
                continue;
            }

            l = r;
        }

        return false;
    };

    int lo{ranges::any_of(A, [K](const int a) { return a <= K; }) ? 1 : 0};
    if (!lo) return 0;
    int hi{sz(A) + 1};

    while (lo + 1 < hi) {
        const auto mid = midpoint(lo, hi);
        if (is_possible(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return lo;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        int K;
        cin >> N >> K;

        vector<int> A(N);
        for (auto &a : A) cin >> a;

        vector<int> H(N);
        for (auto &h : H) cin >> h;

        cout << max_interesting_length(A, H, K) << '\n';
    }

    return 0;
}
