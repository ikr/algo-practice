#include <bits/stdc++.h>
using namespace std;

static constexpr int RO_MAX = 6;
static constexpr int CO_MAX = 6;
static constexpr int DEST_I = (RO_MAX + 1) * (CO_MAX + 1) - 1;

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

    if ((pattern[i] == '?' || pattern[i] == 'U') &&
        is_possible(covered, ro - 1, co)) {
        bool locked = !is_possible(covered, ro - 2, co) &&
                      is_possible(covered, ro - 1, co - 1) &&
                      is_possible(covered, ro - 1, co + 1);

        if (!locked) {
            covered[ro - 1][co] = true;
            recur(pattern, ans, covered, i + 1, ro - 1, co);
            covered[ro - 1][co] = false;
        }
    }

    if ((pattern[i] == '?' || pattern[i] == 'D') &&
        is_possible(covered, ro + 1, co)) {
        bool locked = !is_possible(covered, ro + 2, co) &&
                      is_possible(covered, ro + 1, co - 1) &&
                      is_possible(covered, ro + 1, co + 1);

        if (!locked) {
            covered[ro + 1][co] = true;
            recur(pattern, ans, covered, i + 1, ro + 1, co);
            covered[ro + 1][co] = false;
        }
    }

    if ((pattern[i] == '?' || pattern[i] == 'L') &&
        is_possible(covered, ro, co - 1)) {
        bool locked = !is_possible(covered, ro, co - 2) &&
                      is_possible(covered, ro - 1, co - 1) &&
                      is_possible(covered, ro + 1, co - 1);

        if (!locked) {
            covered[ro][co - 1] = true;
            recur(pattern, ans, covered, i + 1, ro, co - 1);
            covered[ro][co - 1] = false;
        }
    }

    if ((pattern[i] == '?' || pattern[i] == 'R') &&
        is_possible(covered, ro, co + 1)) { // R
        bool locked = !is_possible(covered, ro, co + 2) &&
                      is_possible(covered, ro - 1, co + 1) &&
                      is_possible(covered, ro + 1, co + 1);

        if (!locked) {
            covered[ro][co + 1] = true;
            recur(pattern, ans, covered, i + 1, ro, co + 1);
            covered[ro][co + 1] = false;
        }
    }
}

int matching_paths_count(const string &pattern) {
    vector<vector<bool>> covered(RO_MAX + 1, vector<bool>(CO_MAX + 1, false));
    covered[0][0] = true;
    int ans = 0;
    recur(pattern, ans, covered, 0, 0, 0);
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
