#include <bits/stdc++.h>
using namespace std;

static constexpr int RO_MAX = 6;
static constexpr int CO_MAX = 6;
static constexpr int DEST_I = (RO_MAX + 1) * (CO_MAX + 1) - 1;
static const string ALL_DIRS{"UDLR"};

constexpr pair<int, int> delta(const char dir) {
    switch (dir) {
    case 'U':
        return {-1, 0};
    case 'D':
        return {1, 0};
    case 'L':
        return {0, -1};
    case 'R':
        return {0, 1};
    default:
        assert(false && "Invalid direction char");
        return {0, 0};
    }
}

constexpr bool in_bounds(const int ro, const int co) {
    return ro >= 0 && ro <= RO_MAX && co >= 0 && co <= CO_MAX;
}

constexpr bool is_possible(const vector<vector<bool>> &covered, const int ro,
                           const int co) {
    return in_bounds(ro, co) && !covered[ro][co];
}

int matching_paths_count(const string &pattern) {
    vector<vector<bool>> covered(RO_MAX + 1, vector<bool>(CO_MAX + 1, false));
    covered[0][0] = true;
    int ans = 0;
    function<void(int, int, int)> recur;

    recur = [&recur, &pattern, &ans, &covered](const int i, const int ro,
                                               const int co) {
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

            if (!is_possible(covered, ro_prime + delta_ro,
                             co_prime + delta_co)) {
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
            recur(i + 1, ro_prime, co_prime);
            covered[ro_prime][co_prime] = false;
        }
    };

    recur(0, 0, 0);

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
