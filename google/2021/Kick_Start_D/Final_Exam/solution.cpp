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

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vi solve(const vector<pii> ps, const vi &s) {
    map<int, int> xs;

    for (const auto [a, b] : ps) {
        for (int i = a; i <= b; ++i) {
            ++xs[i];
        }
    }

    vi ans(sz(s), 0);

    for (int i = 0; i < sz(s); ++i) {
        const auto jt = xs.lower_bound(s[i]);
        const auto it = jt == cbegin(xs) ? jt : prev(jt);

        const auto xt = [&]() {
            if (abs(it->first - s[i]) <= abs(jt->first - s[i])) {
                return it;
            } else {
                return jt;
            }
        }();

        ans[i] = xt->first;
        --xt->second;

        if (xt->second == 0) {
            xs.erase(xt);
        }
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
        int n, m;
        cin >> n >> m;

        vector<pii> ps(n);
        for (auto &[a, b] : ps) {
            cin >> a >> b;
        }

        vector<int> ss(m);
        for (auto &s : ss) cin >> s;

        cout << "Case #" << i << ": " << solve(ps, ss) << '\n';
    }

    return 0;
}
