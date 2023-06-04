#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int W, H;
    cin >> W >> H;

    int N;
    cin >> N;

    vector<pair<int, int>> PQ(N);
    for (auto &[p, q] : PQ) cin >> p >> q;

    int na;
    cin >> na;

    vector<int> A(na);
    for (auto &a : A) cin >> a;

    int nb;
    cin >> nb;

    vector<int> B(nb);
    for (auto &b : B) cin >> b;

    map<pair<int, int>, int> hits;
    for (const auto &[p, q] : PQ) {
        const auto i = inof(upper_bound(cbegin(A), cend(A), p) - cbegin(A));
        const auto j = inof(upper_bound(cbegin(B), cend(B), q) - cbegin(B));
        ++hits[{i, j}];
    }

    const auto [lo, hi] = minmax_element(
        cbegin(hits), cend(hits),
        [](const auto &a, const auto &b) { return a.second < b.second; });

    const auto m0 = lo->second;
    const auto m = [&]() -> int {
        if ((na + 1LL) * (nb + 1LL) > 1LL * N) return 0;

        for (int i = 0; i <= na; ++i) {
            for (int j = 0; j <= nb; ++j) {
                if (!hits.count({i, j})) return 0;
            }
        }

        return m0;
    }();

    const auto M = hi->second;

    cout << m << ' ' << M << '\n';
    return 0;
}
