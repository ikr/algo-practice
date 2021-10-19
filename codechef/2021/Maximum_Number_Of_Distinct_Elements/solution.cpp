#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

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

vi optimal_A(const vi &xs) {
    const int hi = *max_element(cbegin(xs), cend(xs));
    vvi idx(hi + 1);

    for (int i = 0; i < sz(xs); ++i) {
        idx[xs[i]].push_back(i);
    }

    vi ans(sz(xs), 0);
    int curr = -1;
    for (int x = 0; x < sz(idx); ++x) {
        for (const int i : idx[x]) {
            curr = min(curr + 1, x - 1);
            ans[i] = curr;
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

        vi xs(n);
        for (auto &x : xs) cin >> x;

        cout << optimal_A(xs) << '\n';
    }

    return 0;
}
