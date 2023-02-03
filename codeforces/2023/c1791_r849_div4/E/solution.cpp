#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll INF = 1e16;

ll max_sum(vector<ll> xs) {
    for (int i = 0; i < sz(xs);) {
        const auto left_win = [&]() -> ll {
            if (i == 0) return -INF;
            return -2LL * (xs[i - 1] + xs[i]);
        }();

        const auto right_win = [&]() -> ll {
            if (i == sz(xs) - 1) return -INF;
            return -2LL * (xs[i] + xs[i + 1]);
        }();

        if (right_win <= 0 && left_win <= 0) {
            ++i;
        } else {
            if (right_win >= left_win) {
                assert(right_win > 0);
                swap(xs[i], xs[i + 1]);
                xs[i] = -xs[i];
                xs[i + 1] = -xs[i + 1];
                i += 2;
            } else {
                assert(right_win < left_win);
                assert(left_win > 0);
                swap(xs[i - 1], xs[i]);
                xs[i - 1] = -xs[i - 1];
                xs[i] = -xs[i];
                i += 1;
            }
        }
    }

    return accumulate(cbegin(xs), cend(xs), 0LL);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<ll> xs(n);
        for (auto &x : xs) cin >> x;

        cout << max_sum(move(xs)) << '\n';
    }

    return 0;
}
