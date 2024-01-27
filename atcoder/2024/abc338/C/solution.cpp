#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int Hi = 1'000'000;
static constexpr int Inf = 1'000'000'000;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> Q(N);
    for (auto &q : Q) cin >> q;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    const auto can_make_k_as = [&](const int k) {
        if (!k) return true;
        for (int i = 0; i < N; ++i) {
            if (!A[i]) continue;
            if (Q[i] / A[i] < k) return false;
        }
        return true;
    };

    vector<int> B(N);
    for (auto &b : B) cin >> b;

    const auto can_make_k_bs = [&](const int ka, const int k) {
        if (!k) return true;
        for (int i = 0; i < N; ++i) {
            if (!B[i]) continue;
            if ((Q[i] - ka * A[i]) / B[i] < k) return false;
        }
        return true;
    };

    int ans{};

    for (int ka = 0; ka <= Hi; ++ka) {
        if (!can_make_k_as(ka)) continue;

        int lo = 0;
        int hi = Inf;

        while (lo + 1 < hi) {
            const int mid = midpoint(lo, hi);
            if (can_make_k_bs(ka, mid)) {
                lo = mid;
            } else {
                hi = mid;
            }
        }

        ans = max(ans, ka + lo);
    }

    cout << ans << '\n';
    return 0;
}
