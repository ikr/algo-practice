#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll INF = 2LL * 1e18;

struct FlightPlan final {
    ll fly(const int R, const int C, const vector<int> &H, const int cup,
           const int cdn, const int clr) const {
        const ll max_h = *max_element(H.cbegin(), H.cend());

        const auto h_at = [&H, C](const int r, const int c) {
            return H[r * C + c];
        };

        vector<vector<vector<ll>>> dp(
            R, vector<vector<ll>>(C, vector<ll>(max_h + 1, INF)));

        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                for (int i = h_at(r, c); i <= max_h; ++i) {
                    if (!r && !c && i == h_at(0, 0)) {
                        dp[r][c][i] = 0;
                        continue;
                    }

                    if (i > 0) {
                        dp[r][c][i] = min(dp[r][c][i], dp[r][c][i - 1] + cup);
                    }
                    if (r > 0) {
                        dp[r][c][i] = min(dp[r][c][i], dp[r - 1][c][i] + clr);
                    }
                    if (c > 0) {
                        dp[r][c][i] = min(dp[r][c][i], dp[r][c - 1][i] + clr);
                    }
                }

                if (!r && !c) continue;
                for (int i = max_h - 1; i >= h_at(r, c); --i) {
                    dp[r][c][i] = min(dp[r][c][i], dp[r][c][i + 1] + cdn);
                }
            }
        }

        return dp[R - 1][C - 1][h_at(R - 1, C - 1)];
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = FlightPlan{}.fly(1, 5, {10, 8, 6, 8, 10}, 40, 10, 20);
        const auto expected = 80;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = FlightPlan{}.fly(6, 1, {10, 8, 16, 18, 8, 12}, 40, 10, 20);
        const auto expected = 480;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
