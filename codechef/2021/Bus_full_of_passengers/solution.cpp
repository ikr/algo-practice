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

bool consistent(const int n, const int m, const vector<pii> &xs) {
    set<int> occ;

    for (const auto [s, x] : xs) {
        if (s == -1) {
            if (x < 0 || x >= n) return false;
            if (!occ.count(x)) return false;
            occ.erase(x);
            continue;
        }

        assert(s == 1);
        if (occ.count(x)) return false;
        occ.insert(x);
        if (sz(occ) > m) return false;
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;

        vector<pii> xs(q);
        for (auto &[s, x] : xs) {
            char sc;
            cin >> sc;

            if (sc == '-') {
                s = -1;
            } else {
                s = 1;
            }

            cin >> x;
            --x;
        }

        cout << (consistent(n, m, xs) ? "Consistent" : "Inconsistent") << '\n';
    }

    return 0;
}
