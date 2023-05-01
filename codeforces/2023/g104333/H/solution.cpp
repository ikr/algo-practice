#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_tri_prod(const vector<int> &xs) {
    ll ans = 1LL * xs[0] * xs[1] * xs[2];
    {
        set<int> xss(cbegin(xs), cend(xs));
        if (sz(xss) == 2) {
            ans = max(ans,
                      1LL * (*cbegin(xss)) * (*cbegin(xss)) * (*crbegin(xss)));
            ans = max(ans,
                      1LL * (*cbegin(xss)) * (*crbegin(xss)) * (*crbegin(xss)));
        }
    }

    set<int> izer;
    set<int> ineg;
    set<int> ipos;
    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] < 0) {
            ineg.insert(i);
        } else if (xs[i] == 0) {
            izer.insert(i);
        } else {
            assert(xs[i] > 0);
            ipos.insert(i);
        }
    }

    vector<int> opts;
    for (const auto &src : {izer, ineg, ipos}) {
        if (sz(src) >= 3) {
            opts.push_back(*next(next(cbegin(src))));
            opts.push_back(*prev(prev(prev(cend(src)))));
        }
        if (sz(src) >= 2) {
            opts.push_back(*next(cbegin(src)));
            opts.push_back(*prev(prev(cend(src))));
        }
        if (sz(src) >= 1) {
            opts.push_back(*cbegin(src));
            opts.push_back(*prev(cend(src)));
        }
    }
    sort(begin(opts), end(opts));
    opts.erase(unique(begin(opts), end(opts)), end(opts));

    for (int i = 0; i < sz(opts) - 2; ++i) {
        for (int j = i + 1; j < sz(opts) - 1; ++j) {
            for (int k = j + 1; k < sz(opts); ++k) {
                ans = max(ans, 1LL * xs[opts[i]] * xs[opts[j]] * xs[opts[k]]);
            }
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

        cout << max_tri_prod(xs) << '\n';
    }

    return 0;
}
