#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

static constexpr int Inf = 100 * 1000 * 1000;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pii optimal_k_range(const int ilo, const int ihi, const vector<int> &ii,
                    const int k) {
    assert(k < sz(ii));
    auto ia0 = ii[0];
    auto ib0 = ii[k - 1];
    auto d0 = max(ihi, ib0) - min(ilo, ia0);

    for (int j = 1; j + k - 1 < sz(ii); ++j) {
        const auto ia = ii[j];
        const auto ib = ii[j + k - 1];
        const auto d = max(ihi, ib) - min(ilo, ia);
        if (d < d0) {
            ia0 = ia;
            ib0 = ib;
            d0 = d;
        }
    }

    return {ia0, ib0};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    map<int, vector<int>> idx;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        idx[a].push_back(i);
    }

    int ilo = Inf;
    int ihi = -Inf;
    for (const auto &[_, ii] : idx) {
        const auto taking = min(m, sz(ii));
        if (taking == sz(ii)) {
            ilo = min(ilo, ii.front());
            ihi = max(ihi, ii.back());
        } else {
            assert(taking < sz(ii));
            const auto [ia, ib] = optimal_k_range(ilo, ihi, ii, taking);
            ilo = min(ilo, ia);
            ihi = max(ihi, ib);
        }

        m -= taking;
        if (!m) break;
    }

    cout << (ihi - ilo + 1) << '\n';
    return 0;
}
