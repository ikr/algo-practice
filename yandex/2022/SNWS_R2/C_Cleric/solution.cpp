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
    vector<int> outcomes(n + 1, 0);
    assert(n >= 6);
    for (int i = 1; i <= 6; ++i) ++outcomes[i];

    for (auto [ans, tail] = pair{1, 0LL};; ++ans) {
        const auto hi = outcomes[n] + tail;
        const auto lo = accumulate(cbegin(outcomes), cbegin(outcomes) + n, 0);
        if (doof(hi) / doof(lo) >= p) return ans;

        tail *= 6;
        long long addition_to_tail{};
        auto outcomes_ = outcomes;

        for (int k = 1; k <= n; ++k) {
            if (!outcomes[k]) continue;

            for (int i = 1; i <= 6; ++i) {
                if (k + i <= n) {
                    ++outcomes_[sfs.count(k + i) ? sfs.at(k + i) : (k + i)];
                } else {
                    ++addition_to_tail;
                }
            }
        }

        tail += addition_to_tail;
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
