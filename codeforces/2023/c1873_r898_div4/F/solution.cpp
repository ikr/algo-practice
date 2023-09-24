#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pii> all_proper_height_intervals(const vector<int> &H) {
    vector<pii> result;
    for (int l{}, r{}; l < sz(H);) {
        assert(l <= r);
        while (r + 1 <= sz(H) - 1 && (H[r] % H[r + 1]) == 0LL) ++r;
        result.emplace_back(l, r);

        if (l == r) {
            ++l;
            ++r;
        } else {
            l = r + 1;
            r = l;
        }
    }

    return result;
}

int max_interesting_length(const vector<int> &A, const vector<int> &H,
                           const int K) {
    int lo{ranges::any_of(A, [K](const int a) { return a <= K; }) ? 1 : 0};
    if (!lo) return 0;

    vector<int> ss(sz(A) + 1, 0);
    partial_sum(cbegin(A), cend(A), begin(ss) + 1);
    const auto phi = all_proper_height_intervals(H);

    const auto is_possible = [&](const int d) -> bool {
        for (const auto &[l, r] : phi) {
            if (r - l + 1 < d) continue;
            for (int x = l, y = l + d - 1; y <= r; ++x, ++y) {
                if (ss[y + 1] - ss[x] <= K) return true;
            }
        }
        return false;
    };

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
