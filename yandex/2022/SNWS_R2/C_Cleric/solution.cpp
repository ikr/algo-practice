#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;

using Real = long double;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr Real EPS = 0.000001;

bool target_reached(const int n, const Real p, const vector<Real> &dp) {
    assert(n < sz(dp));
    const auto actual = accumulate(next(cbegin(dp), n), cend(dp), 0.0);
    return actual >= p;
}

int min_fights(const int n, const Real p, const vector<int> &sfs) {
    // dp[i] — probability of reaching exactly the level i after the current
    // number of battles
    vector<Real> dp(n + 5 + 1, 0.0);
    dp[0] = 1.0;
    int result{};

    while (!target_reached(n, p, dp)) {
        vector<Real> dp_(sz(dp), 0.0);

        for (int i = 0; i < sz(dp); ++i) {
            for (int j = 1; j <= 6; ++j) {
                const auto new_level = min(sz(dp) - 1, i + j);
                dp_[sfs[new_level]] += dp[i] / 6.0;
            }
        }

        swap(dp, dp_);
        ++result;
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    Real p;
    cin >> p;

    vector<int> sfs(n + 5 + 1);
    iota(begin(sfs), end(sfs), 0);

    for (int i = 0; i < k; ++i) {
        int s, f;
        cin >> s >> f;
        sfs[s] = f;
    }

    cout << min_fights(n, p, sfs) << '\n';
    return 0;
}

// AJN 2022-01-20 https://contest.yandex.ru/snws2022/contest/23958/problems/C/
