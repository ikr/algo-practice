#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

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
using pii = pair<int, int>;
using pll = pair<ll, ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll simulate(const vector<int> &xs, const int ia, const int ib) {
    const auto N = sz(xs);
    const auto in_bounds = [N](const int i) -> bool { return 0 <= i && i < N; };

    vector<pll> outcomes;
    for (const auto &[da, db] :
         vector<pii>{{-1, -1}, {-1, 1}, {1, -1}, {1, 1}}) {
        ll ra{xs[ia]};
        ll rb{xs[ib]};
        vector<bool> av(N, true);
        av[ia] = false;
        av[ib] = false;

        int i = ia;
        int j = ib;

        while ((in_bounds(i + da) && av[i + da]) ||
               (in_bounds(j + db) && av[j + db])) {
            if (in_bounds(i + da) && av[i + da]) {
                i += da;
                av[i] = false;
                ra += xs[i];
            }

            if (in_bounds(j + db) && av[j + db]) {
                j += db;
                av[j] = false;
                rb += xs[j];
            }
        }

        outcomes.emplace_back(ra, rb);
    }

    sort(begin(outcomes), end(outcomes), [](const pll &lhs, const pll &rhs) {
        return abs(lhs.first - lhs.second) < abs(rhs.first - rhs.second);
    });
    cerr << outcomes << endl;
    return -1;
}

ll solve(const vector<int> &xs, const pii sa, const pii sb) {
    ll ans{};
    for (auto ia = sa.first; ia <= sa.second; ++ia) {
        for (auto ib = sb.first; ib <= sb.second; ++ib) {
            if (ia == ib) continue;
            ans = max(ans, simulate(xs, ia, ib));
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<int> xs(N);
        for (auto &x : xs) cin >> x;

        pii sa, sb;
        cin >> sa.first >> sa.second >> sb.first >> sb.second;
        --sa.first;
        --sa.second;
        --sb.first;
        --sb.second;

        cout << "Case #" << i << ": " << solve(xs, sa, sb) << '\n';
    }

    return 0;
}
