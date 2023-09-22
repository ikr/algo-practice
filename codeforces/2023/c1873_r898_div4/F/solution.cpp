#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_interesting_length(const vector<int> &A, const vector<int> &H,
                           const int K) {
    vector<int> ss(sz(A));
    partial_sum(cbegin(A), cend(A), begin(ss));
    const auto yield_within = [&](const int l, const int r) {
        assert(0 <= l && l <= r && r < sz(ss));
        return ss[r] - (l ? ss[l - 1] : 0LL);
    };

    int l{};
    int r{};
    int result{ranges::any_of(A, [K](const int a) { return a <= K; }) ? 1 : 0};

    while (l < sz(A)) {
        if (l == sz(A) - 1) break;

        while (r + 1 <= sz(A) - 1 && (H[r] % H[r + 1]) == 0 &&
               yield_within(l, r + 1) <= K) {
            ++r;
            result = max(result, r - l + 1);
        }

        if (r == l) {
            ++l;
            ++r;
            continue;
        }

        l = r;
    }

    return result;
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
