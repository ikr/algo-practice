#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_fights(const int n, const double p, const map<int, int> &sfs) {
    vector<int> outcomes(n + 2, 0);
    for (int i = 1; i <= 6; ++i) ++outcomes[min(i, n + 1)];

    for (int ans = 1;; ++ans) {
        const auto hi = outcomes[n] + outcomes[n + 1];
        const auto lo =
            accumulate(cbegin(outcomes) + 1, cbegin(outcomes) + n, 0);
        if (doof(hi) / doof(lo) >= p) return ans;

        auto outcomes_ = outcomes;

        for (int k = 1; k <= n + 1; ++k) {
            if (!outcomes[k]) continue;

            for (int i = 1; i <= 6; ++i) {
                const auto newval_src = min(k + i, n + 1);
                const auto newval =
                    sfs.count(newval_src) ? sfs.at(newval_src) : newval_src;
                ++outcomes_[newval];
            }
        }

        swap(outcomes, outcomes_);
    }

    return -1;
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
