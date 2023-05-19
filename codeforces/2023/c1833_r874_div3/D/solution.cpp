#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> optimal(vector<int> xs) {
    if (sz(xs) == 1) return xs;
    if (sz(xs) == 2) {
        reverse(begin(xs), end(xs));
        return xs;
    }

    auto ans = xs;
    for (int i = 0; i < sz(xs); ++i) {
        for (int j = i; j < sz(xs); ++j) {
            vector cur(cbegin(xs) + j + 1, cend(xs));
            for (int k = j; k >= i; --k) {
                cur.push_back(xs[k]);
            }
            cur.insert(cend(cur), cbegin(xs), cbegin(xs) + i);

            if (cur > ans) swap(cur, ans);
        }
    }
    return ans;
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

        cout << optimal(move(xs)) << '\n';
    }

    return 0;
}
