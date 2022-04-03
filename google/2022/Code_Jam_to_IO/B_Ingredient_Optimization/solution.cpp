#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

struct Delivery final {
    int M;
    int L;
    int E;
};

vector<vector<int>> coverage(const vector<Delivery> &ds,
                             const vector<int> &os) {
    vector<vector<int>> result(sz(os));

    for (int k = 0; k < sz(ds); ++k) {
        const auto &d = ds[k];
        const auto rightmost = d.M + d.E - 1;
        const auto it = lower_bound(cbegin(os), cend(os), d.M);
        if (it == cend(os) || rightmost < *it) continue;

        const auto jt = [&]() -> vector<int>::const_iterator {
            const auto ii = lower_bound(it, cend(os), rightmost);
            if (ii != cend(os) && *ii == rightmost) return ii;
            return prev(ii);
        }();

        const auto i0 = inof(distance(cbegin(os), it));
        const auto i1 = inof(distance(cbegin(os), jt));
        for (int i = i0; i <= i1; ++i) {
            result[i].push_back(k);
        }
    }

    for (auto &ii : result) {
        sort(begin(ii), end(ii), [&](const int i, const int j) {
            return (ds[i].M + ds[i].E) < (ds[j].M + ds[j].E);
        });
    }

    return result;
}

// The plan
//
// O₁ O₂ …
//
// A. Let's collect for every Oᵢ (1 <= i <= N) the indices 1 <= j <= D of
// deliveries covering it. Then, let's sort every “bucket” of indices j by the
// leaves' expiration time. Thus, we shall first favor the leaves expiring
// sooner.
//
// B. Scan Oᵢ-s in ascending order, maintaining the unused capacities of every
// delivery. If there are no deliveries with enough positive remaining capacity
// covering the current order (to yield U leaves total), we have to stop
// cooking.
//
int solve(const int U, vector<Delivery> ds, const vector<int> &os) {
    const auto cov = coverage(ds, os);
    assert(sz(cov) == sz(os));

    for (int k = 0; k < sz(os); ++k) {
        int curr{};

        for (const int i : cov[k]) {
            if (curr == U) break;
            const auto d = min(U - curr, ds[i].L);
            curr += d;
            ds[i].L -= d;
        }

        if (curr < U) return k;
    }

    return sz(os);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int D, N, U;
        cin >> D >> N >> U;

        vector<Delivery> ds(D);
        for (auto &[M, L, E] : ds) cin >> M >> L >> E;

        vector<int> os(N);
        for (auto &o : os) cin >> o;

        cout << "Case #" << i << ": " << solve(U, move(ds), os) << '\n';
    }

    return 0;
}
