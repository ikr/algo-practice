#include <bits/stdc++.h>
using namespace std;

using ll = long long;

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int cycle(const int x) { return ((x - 1) % 10) + 1; }

vector<vvi> outcomes(const int starting_space) {
    // dp[i][j][k] is the number of ways for a player starting at the
    // `starting_space` to obtain the score `i` after exactly `j` moves, ending
    // up at the space `k`.
    vector<vvi> dp(31, vvi(22, vi(11, 0)));
    dp[0][0][starting_space] = 1;

    for (int i = 0; i < 21; ++i) {
        for (int j = 0; j < sz(dp[i]); ++j) {
            for (int k = 1; k <= 10; ++k) {
                for (int d = 1; d <= 3; ++d) {
                    if (j + 1 >= sz(dp[0])) continue;
                    dp[i + cycle(k + d)][j + 1][cycle(k + d)] += dp[i][j][k];
                }
            }
        }
    }

    return dp;
}

ll count_wins(const vector<vvi> &own_dp, const vector<vvi> &other_dp,
              const int other_moves_delta) {
    ll ans{};

    for (int score = 21; score < sz(own_dp); ++score) {
        for (int moves = 3; moves < sz(own_dp[score]); ++moves) {
            const int other_moves = moves + other_moves_delta;

            ll own_outcomes{};
            for (int space = 1; space <= 10; ++space) {
                own_outcomes += own_dp[score][moves][space];
            }

            ll other_outcomes{};
            for (int i = 0; i < 21; ++i) {
                for (int k = 1; k <= 10; ++k) {
                    other_outcomes += other_dp[i][other_moves][k];
                }
            }

            ans += own_outcomes * other_outcomes;
        }
    }

    return ans;
}

ll winning_universes_num(const array<int, 2> &xs) {
    const auto dp0 = outcomes(xs[0]);
    const auto dp1 = outcomes(xs[1]);
    return max(count_wins(dp0, dp1, -1), count_wins(dp1, dp0, 0));
}

int main() {
    array<int, 2> xs;
    for (int i = 0; i < 2; ++i) {
        string line;
        getline(cin, line);

        const auto sep = line.find(": ");
        xs[i] = stoi(line.substr(sep + 2));
    }

    cout << winning_universes_num(xs) << '\n';
    return 0;
}
