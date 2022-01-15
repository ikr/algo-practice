#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_fights(const int n, const double p, const map<int, int> &sfs) {
    vector<int> outcomes(n + 2, 0);
    int ans = 1;

    for (int i = 1; i <= 6; ++i) {
        if (i < sz(outcomes)) {
            ++outcomes[i];
        } else {
            ++outcomes.back();
        }
    }

    for (;; ++ans) {
        const double hi = outcomes[n] + outcomes[n + 1];
        const double lo = accumulate(cbegin(outcomes) + 1, cbegin(outcomes) + n,
                                     0.0, plus<double>{});
        if (hi / lo >= p) return ans;

        auto outcomes_ = outcomes;

        for (int k = 1; k <= n; ++k) {
            if (!outcomes[k]) continue;

            for (int i = 1; i <= 6; ++i) {
                const auto newval_src =
                    k + i < sz(outcomes) ? (k + i) : (n + 1);
                const auto newval =
                    sfs.count(newval_src) ? sfs.at(newval_src) : newval_src;
                ++outcomes_[newval];
            }
        }

        swap(outcomes, outcomes_);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    double p;
    cin >> p;

    map<int, int> sfs;
    for (int i = 0; i < k; ++i) {
        int s, f;
        cin >> s >> f;
        sfs[s] = f;
    }

    cout << min_fights(n, p, sfs) << '\n';
    return 0;
}
