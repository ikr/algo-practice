#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_interesting_length(const vector<ll> &A, const vector<ll> &H,
                           const ll K) {
    vector<ll> ss(sz(A));
    partial_sum(cbegin(A), cend(A), begin(ss));
    const auto yield_within = [&](const int l, const int r) {
        assert(0 <= l && l <= r && r < sz(ss));
        return ss[r] - (l ? ss[l - 1] : 0LL);
    };

    int l = 0;
    int r = 0;
    int result = yield_within(l, r) < K ? 1 : 0;

    while (l < sz(A)) {
        if (l == sz(A) - 1) {
            if (yield_within(l, l) < K) result = max(result, 1);
            break;
        }

        if ((H[l] % H[l + 1]) != 0) {
            if (yield_within(l, l) < K) result = max(result, 1);
            ++l;
            r = l;
            // cerr << "l: " << l << ", r: " << r << endl;
            continue;
        }

        while (r + 1 <= sz(A) - 1 && (H[r] % H[r + 1]) == 0 &&
               yield_within(l, r + 1) < K) {
            ++r;
            // cerr << "l: " << l << ", r: " << r << endl;
            result = max(result, r - l + 1);
        }
        if (r == l) {
            if (yield_within(l, l) < K) result = max(result, 1);
            ++l;
            ++r;
            // cerr << "l: " << l << ", r: " << r << endl;
            continue;
        }

        l = r;
        // cerr << "l: " << l << ", r: " << r << endl;
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
        ll K;
        cin >> N >> K;

        vector<ll> A(N);
        for (auto &a : A) cin >> a;

        vector<ll> H(N);
        for (auto &h : H) cin >> h;

        cout << max_interesting_length(A, H, K) << '\n';
    }

    return 0;
}
