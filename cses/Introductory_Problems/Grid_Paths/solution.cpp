#include <bits/stdc++.h>
using namespace std;

static constexpr int RO_MAX = 6;
static constexpr int CO_MAX = 6;
static constexpr int DEST_I = (RO_MAX + 1) * (CO_MAX + 1) - 1;
static const string ALL_DIRS{"UDLR"};

static constexpr pair<int, int> UP{-1, 0};
static constexpr pair<int, int> DOWN{1, 0};
static constexpr pair<int, int> LEFT{0, -1};
static constexpr pair<int, int> RIGHT{0, 1};
static constexpr pair<int, int> ZERO{0, 0};

constexpr const pair<int, int> &delta(const char dir) {
    switch (dir) {
    case 'U':
        return UP;
    case 'D':
        return DOWN;
    case 'L':
        return LEFT;
    case 'R':
        return RIGHT;
    default:
        assert(false && "Invalid direction char");
        return ZERO;
    }
}

constexpr bool in_bounds(const int ro, const int co) {
    return ro >= 0 && ro <= RO_MAX && co >= 0 && co <= CO_MAX;
}

constexpr bool is_possible(const vector<vector<bool>> &covered, const int ro,
                           const int co) {
    return in_bounds(ro, co) && !covered[ro][co];
}

void recur(const string &pattern, int &ans, vector<vector<bool>> &covered,
           const int i, const int ro, const int co) {
    if (ro == RO_MAX && co == 0) {
        if (i == DEST_I) ++ans;
        return;
    }

    for (const auto dir :
         pattern[i] == '?' ? ALL_DIRS : string(1, pattern[i])) {
        const auto [delta_ro, delta_co] = delta(dir);
        const int ro_prime = ro + delta_ro;
        const int co_prime = co + delta_co;

        if (!is_possible(covered, ro_prime, co_prime)) continue;

        if (!is_possible(covered, ro_prime + delta_ro, co_prime + delta_co)) {
            switch (dir) {
            case 'U':
            case 'D':
                if (is_possible(covered, ro_prime, co_prime - 1) &&
                    is_possible(covered, ro_prime, co_prime + 1))
                    continue;
                break;

            case 'L':
            case 'R':
                if (is_possible(covered, ro_prime - 1, co_prime) &&
                    is_possible(covered, ro_prime + 1, co_prime))
                    continue;
                break;
            }
        }

        covered[ro_prime][co_prime] = true;
        recur(pattern, ans, covered, i + 1, ro_prime, co_prime);
        covered[ro_prime][co_prime] = false;
    }
}

int matching_paths_count(const string &pattern) {
    vector<vector<bool>> covered(RO_MAX + 1, vector<bool>(CO_MAX + 1, false));
    covered[0][0] = true;
    int ans = 0;
    recur(pattern, ans, covered,0, 0, 0);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;
    cout << matching_paths_count(s) << '\n';

    return 0;
}
