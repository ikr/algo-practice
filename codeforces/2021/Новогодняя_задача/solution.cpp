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
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pii col_two_his(const vvi &joy, const int co) {
    const int m = sz(joy);
    set<int> ans;

    for (int ro = 0; ro < m; ++ro) {
        ans.insert(joy[ro][co]);
        if (sz(ans) > 2) {
            ans.erase(cbegin(ans));
        }
    }

    assert(sz(ans) == 2);
    return {*crbegin(ans), *cbegin(ans)};
}

int max_alpha(const vvi &joy) {
    const int m = sz(joy);
    const int n = sz(joy[0]);

    vector<pii> cth(n);
    for (int co = 0; co < n; ++co) {
        cth[co] = col_two_his(joy, co);
    }

    int ans{};

    for (int ro = 0; ro < m; ++ro) {
        vi a(n, 0);

        for (int co = 0; co < n; ++co) {
            const auto [one, two] = cth[co];

            if (joy[ro][co] == one) {
                a[co] = max(two, a[co]);
            } else {
                a[co] = max(one, a[co]);
            }
        }

        cerr << "ro:" << ro << " a:" << a << endl;

        ans = max(ans, *min_element(cbegin(a), cend(a)));
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int m, n;
        cin >> m >> n;

        vvi joy(m, vi(n, 0));
        for (auto &row : joy) {
            for (auto &x : row) {
                cin >> x;
            }
        }

        cout << max_alpha(joy) << '\n';
    }

    return 0;
}
