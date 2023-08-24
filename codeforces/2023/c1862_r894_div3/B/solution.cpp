#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        vector<int> ans{xs[0]};
        ans.reserve(sz(xs));

        for (int i = 1; i < sz(xs); ++i) {
            if (xs[i - 1] <= xs[i]) {
                ans.push_back(xs[i]);
            } else {
                ans.push_back(xs[i]);
                ans.push_back(xs[i]);
            }
        }

        cout << sz(ans) << '\n' << ans << '\n';
    }

    return 0;
}
