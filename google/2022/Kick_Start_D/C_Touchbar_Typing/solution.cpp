#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

static constexpr ll INF = 1e18;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll min_time(const vector<int> &S, const vector<int> &K) {
    const auto N = sz(S);
    const auto M = sz(K);

    map<int, vector<int>> idx;
    for (int i = 0; i < sz(K); ++i) {
        idx[K[i]].push_back(i);
    }

    vector<vector<ll>> dp(N, vector(M, INF));
    vector<ll> lo(N, INF);
    vector<int> loi(N, -1);

    for (int j = 0; j < sz(idx[S[0]]); ++j) {
        dp[0][j] = 0;
    }
    lo[0] = 0;
    loi[0] = 0;

    for (int i = 1; i < N; ++i) {
        const vector<int> &sources = idx.at(S[i - 1]);
        const vector<int> &targets = idx.at(S[i]);

        for (int j1 = 0; j1 < sz(targets); ++j1) {
            {
                auto it =
                    lower_bound(cbegin(sources), cend(sources), targets[j1]);
                const auto jt = it == cbegin(sources) ? it : prev(it);
                if (it == cend(sources)) it = prev(it);

                const auto j0 = [&]() -> int {
                    if (abs(*it - targets[j1]) < abs(*jt - targets[j1])) {
                        return inof(distance(cbegin(sources), it));
                    } else {
                        return inof(distance(cbegin(sources), jt));
                    }
                }();

                if (dp[i - 1][j0] + abs(sources[j0] - targets[j1]) < lo[i]) {
                    lo[i] = dp[i - 1][j0] + abs(sources[j0] - targets[j1]);
                    loi[i] = j1;
                }

                dp[i][j1] = min(dp[i][j1],
                                dp[i - 1][j0] + abs(sources[j0] - targets[j1]));
            }

            {
                const auto j0 = loi[i - 1];
                if (dp[i - 1][j0] + abs(sources[j0] - targets[j1]) < lo[i]) {
                    lo[i] = dp[i - 1][j0] + abs(sources[j0] - targets[j1]);
                    loi[i] = j1;
                }

                dp[i][j1] = min(dp[i][j1],
                                dp[i - 1][j0] + abs(sources[j0] - targets[j1]));
            }
        }

        // for (int j0 = 0; j0 < sz(sources); ++j0) {
        //     for (int j1 = 0; j1 < sz(targets); ++j1) {
        //         dp[i][j1] = min(dp[i][j1],
        //                         dp[i - 1][j0] + abs(sources[j0] -
        //                         targets[j1]));
        //     }
        // }
    }

    return *min_element(cbegin(dp.back()), cend(dp.back()));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<int> S(N);
        for (auto &x : S) cin >> x;

        int M;
        cin >> M;

        vector<int> K(M);
        for (auto &x : K) cin >> x;

        cout << "Case #" << i << ": " << min_time(S, K) << '\n';
    }

    return 0;
}
