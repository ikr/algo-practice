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

using Tri = tuple<int, int, int>;

vector<Tri> ops_seq(vi xs) {
    vector<Tri> ans;

    int pre = 0;
    while (pre + 1 < sz(xs)) {
        const auto it = min_element(begin(xs) + pre, end(xs));

        const auto d = distance(begin(xs) + pre, it);
        if (d) ans.emplace_back(pre, sz(xs), d);

        rotate(begin(xs) + pre, it, end(xs));
        ++pre;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;

        const auto ans = ops_seq(xs);
        cout << sz(ans) << '\n';

        for (const auto [l, r, d] : ans) {
            cout << (l + 1) << ' ' << r << ' ' << d << '\n';
        }
    }

    return 0;
}
