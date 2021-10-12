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

array<set<int>, 10> indices_by_digit(const string &xs) {
    array<set<int>, 10> ans{};
    for (int i = 0; i < sz(xs); ++i) {
        const int d = inof(xs[i]) - inof('0');
        ans[d].insert(i);
    }
    return ans;
}

ll nice_pairs(const string &xs) {
    const auto idx = indices_by_digit(xs);
    ll ans = 0;

    for (int i = 0; i < sz(xs); ++i) {
        const int d = inof(xs[i]) - inof('0');

        for (int k = 0; k < 10; ++k) {
            if (k == d) continue;
            const int delta = abs(k - d);
            if (idx[k].count(i + delta)) ++ans;
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
    while (t--) {
        int n;
        cin >> n;

        string xs(n, ' ');
        cin >> xs;

        cout << nice_pairs(xs) << '\n';
    }

    return 0;
}
