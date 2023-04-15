#include <bits/stdc++.h>
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
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll simulate(const vector<int> &xs, const int ia, const int ib) {
    const auto N = sz(xs);
    const auto in_bounds = [N](const int i) -> bool { return 0 <= i && i < N; };

    ll ans{};
    for (const auto &[da, db] :
         vector<pii>{{-1, -1}, {-1, 1}, {1, -1}, {1, 1}}) {
        cerr << "da:" << da << " db:" << db << endl;
        ll sub{xs[ia]};
        vector<bool> av(N, true);
        av[ia] = false;
        av[ib] = false;
        cerr << "av:" << av << endl;

        int i = ia;
        int j = ib;

        while (in_bounds(i + da) && av[i + da]) {
            i += da;
            av[i] = false;
            sub += xs[i];

            if (in_bounds(j + db) && av[j + db]) {
                j += db;
                av[j] = false;
            }
            cerr << "av:" << av << endl;
        }

        cerr << "sub:" << sub << endl << endl;
        ans = max(ans, sub);
    }
    return ans;
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
