#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> &lhs, const pair<T, T> &rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

static const vector<pi> NEIGH_DELTAS{{-1, 0}, {-1, 1}, {0, 1},  {1, 1},
                                     {1, 0},  {1, -1}, {0, -1}, {-1, -1}};

char get_at(const vector<string> &rows, const pi rc) {
    const int h = rows.size();
    if (!h) return '.';
    const int w = rows[0].size();

    const int ro = rc.first;
    const int co = rc.second;

    return ro >= 0 && ro < h && co >= 0 && co < w ? rows[ro][co] : '.';
}

vector<pi> gather_neigh_coords(const pi rc) {
    vector<pi> ans(NEIGH_DELTAS.size());
    transform(NEIGH_DELTAS.cbegin(), NEIGH_DELTAS.cend(), begin(ans),
              [rc](const pi d) { return rc + d; });
    return ans;
}

string gather_neighs(const vector<string> &rows, const pi rc) {
    const auto neigh_coords = gather_neigh_coords(rc);
    string ans(neigh_coords.size(), ' ');
    transform(neigh_coords.cbegin(), neigh_coords.cend(), begin(ans),
              [&rows](const pi rc) { return get_at(rows, rc); });
    return ans;
}

int count_neighs(const vector<string> &rows, const pi rc) {
    const auto neighs = gather_neighs(rows, rc);
    return count(neighs.cbegin(), neighs.cend(), '*');
}

vector<string> reveal(const vector<string> &rows) {
    const int h = rows.size();
    if (!h) return {};
    const int w = rows[0].size();

    vector<string> ans = rows;

    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            if (rows[ro][co] == '*') continue;
            ans[ro][co] = '0' + count_neighs(rows, {ro, co});
        }
    }

    return ans;
}

int main() {
    for (int i = 1;; ++i) {
        int h, w;
        cin >> h >> w;

        if (!h && !w) break;
        if (i != 1) cout << '\n';

        vector<string> rows(h, string(w, ' '));
        for (auto &row : rows) cin >> row;

        const auto rows_ = reveal(rows);
        cout << "Field #" << i << ":\n";

        for (const auto &row : rows_) cout << row << '\n';
    }

    return 0;
}
