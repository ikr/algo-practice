#include <algorithm>
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

using ll = long long;

vector<ll> capacity(const vector<Delivery> &ds, const vector<int> &os) {
    vector<ll> result(sz(os), 0);

    for (const auto &d : ds) {
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
            result[i] += d.L;
        }
    }

    return result;
}

int solve(const ll U, const vector<Delivery> &ds, const vector<int> &os) {
    const auto cap = capacity(ds, os);
    int result{};

    for (const auto c : cap) {
        if (c < U) break;
        ++result;
    }

    return result;
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

        cout << "Case #" << i << ": " << solve(U, ds, os) << '\n';
    }

    return 0;
}
