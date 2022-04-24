#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll INF = 1e18;

ll solve(const vector<vector<int>> &xss) {
    const auto N = sz(xss);
    assert(N <= 10);
    const auto P = sz(xss[0]);

    ll result = INF;
    vector<int> ord(N);
    iota(begin(ord), end(ord), 0);

    do {
        vector<ll> up(P, INF);
        up[0] = xss[ord[0]].back();
        vector<ll> dn(P, INF);
        dn[0] = xss[ord[0]].back() + xss[ord[0]].back() - xss[ord[0]][0];

        for (int i = 1; i < P; ++i) {
            up[i] =
                min(up[i - 1] + abs(xss[ord[i - 1]].back() - xss[ord[i]][0]) +
                        xss[ord[i]].back() - xss[ord[i]][0],
                    dn[i - 1] + abs(xss[ord[i - 1]][0] - xss[ord[i]][0]) +
                        xss[ord[i]].back() - xss[ord[i]][0]);

            dn[i] = min(
                up[i - 1] + abs(xss[ord[i - 1]].back() - xss[ord[i]].back()) +
                    xss[ord[i]].back() - xss[ord[i]][0],
                dn[i - 1] + abs(xss[ord[i - 1]][0] - xss[ord[i]].back()) +
                    xss[ord[i]].back() - xss[ord[i]][0]);
        }

        result = min(result, min(up.back(), dn.back()));
    } while (next_permutation(begin(ord), end(ord)));

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, P;
        cin >> N >> P;

        vector<vector<int>> xss(N, vector<int>(P, 0));
        for (auto &xs : xss) {
            for (auto &x : xs) cin >> x;
            sort(begin(xs), end(xs));
        }

        cout << "Case #" << i << ": " << solve(xss) << '\n';
    }

    return 0;
}
