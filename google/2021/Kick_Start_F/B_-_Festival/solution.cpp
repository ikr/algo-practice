#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Tri = tuple<int, int, int>;

ll solve_brute(const int D, const vector<Tri> &atts, const int K) {
    vvll tbl(D);

    for (const auto [h, s, e] : atts) {
        for (int i = s; i <= e; ++i) {
            tbl[i].push_back(h);
        }
    }

    ll ans = 0;

    for (int i = 0; i < D; ++i) {
        sort(rbegin(tbl[i]), rend(tbl[i]));

        const auto candidate = accumulate(
            cbegin(tbl[i]), cbegin(tbl[i]) + min(K, sz(tbl[i])), 0LL);

        ans = max(ans, candidate);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int D, N, K;
        cin >> D >> N >> K;

        vector<Tri> atts(N);
        for (auto &[h, s, e] : atts) {
            cin >> h >> s >> e;
            --s;
            --e;
        }

        cout << "Case #" << i << ": " << solve_brute(D, atts, K) << '\n';
    }

    return 0;
}
