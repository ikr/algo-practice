#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> transpose(const vector<vector<int>> &grid) {
    vector<vector<int>> result(sz(grid[0]), vector(sz(grid), 0));

    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[0]); ++co) {
            result[co][ro] = grid[ro][co];
        }
    }

    return result;
}

vector<vector<int>> sort_every_row_then_sort_rows(vector<vector<int>> grid) {
    for (auto &row : grid) {
        sort(begin(row), end(row));
    }
    sort(begin(grid), end(grid));
    return grid;
}

bool are_isomorphic(const vector<vector<int>> &A,
                    const vector<vector<int>> &B) {
    const auto h = sz(A);
    const auto w = sz(A[0]);
    if (h == 1 || w == 1) return true;

    return sort_every_row_then_sort_rows(A) ==
               sort_every_row_then_sort_rows(B) &&
           sort_every_row_then_sort_rows(transpose(A)) ==
               sort_every_row_then_sort_rows(transpose(B));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int h, w;
        cin >> h >> w;

        vector<vector<int>> A(h, vector(w, 0));
        for (auto &ra : A) {
            for (auto &a : ra) {
                cin >> a;
                --a;
            }
        }

        vector<vector<int>> B(h, vector(w, 0));
        for (auto &rb : B) {
            for (auto &b : rb) {
                cin >> b;
                --b;
            }
        }

        cout << (are_isomorphic(A, B) ? "YES" : "NO") << '\n';
    }

    return 0;
}
