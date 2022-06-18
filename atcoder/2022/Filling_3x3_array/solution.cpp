#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> possible_summands(const int s) {
    vector<vector<int>> result;

    for (int i = 1; i <= s; ++i) {
        for (int j = 1; j <= s; ++j) {
            if (i + j > s) break;

            for (int k = 1; k <= s; ++k) {
                if (i + j + k > s) break;
                if (i + j + k == s) result.push_back(vector{i, j, k});
            }
        }
    }

    return result;
}

using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int h1, h2, h3, w1, w2, w3;
    cin >> h1 >> h2 >> h3 >> w1 >> w2 >> w3;

    vector<vector<set<int>>> h_opt(3, vector(3, set<int>{}));

    {
        for (const auto &ijk : possible_summands(h1)) {
            for (int co = 0; co < 3; ++co) {
                h_opt[0][co].insert(ijk[co]);
            }
        }

        for (const auto &ijk : possible_summands(h2)) {
            for (int co = 0; co < 3; ++co) {
                h_opt[1][co].insert(ijk[co]);
            }
        }

        for (const auto &ijk : possible_summands(h3)) {
            for (int co = 0; co < 3; ++co) {
                h_opt[2][co].insert(ijk[co]);
            }
        }
    }

    vector<vector<set<int>>> w_opt(3, vector(3, set<int>{}));

    {
        for (const auto &ijk : possible_summands(w1)) {
            for (int ro = 0; ro < 3; ++ro) {
                w_opt[ro][0].insert(ijk[ro]);
            }
        }

        for (const auto &ijk : possible_summands(w2)) {
            for (int ro = 0; ro < 3; ++ro) {
                w_opt[ro][1].insert(ijk[ro]);
            }
        }

        for (const auto &ijk : possible_summands(w3)) {
            for (int ro = 0; ro < 3; ++ro) {
                w_opt[ro][2].insert(ijk[ro]);
            }
        }
    }

    ll result = 1;

    for (int ro = 0; ro < 3; ++ro) {
        for (int co = 0; co < 3; ++co) {
            vector<int> X;
            set_intersection(cbegin(h_opt[ro][co]), cend(h_opt[ro][co]),
                             cbegin(w_opt[ro][co]), cend(w_opt[ro][co]),
                             back_inserter(X));
            result *= sz(X);
        }
    }

    cout << result << '\n';
    return 0;
}
