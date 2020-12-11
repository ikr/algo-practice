#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

template <typename Iter, typename R, typename Binop, typename Unaop>
R ttransform_reduce(Iter first, Iter last, R init, Binop binop, Unaop unaop) {
    R ans = init;

    for (auto it = first; it != last; ++it) {
        ans = binop(ans, unaop(*it));
    }

    return ans;
}

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> &lhs, const pair<T, T> &rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

char get_v(const vector<string> &rows, const pi rc) {
    const int H = rows.size();
    const int W = rows[0].size();

    const auto [ro, co] = rc;
    if (ro < 0 || ro >= H || co < 0 || co >= W) return '.';
    return rows[ro][co];
}

vector<pi> neighs(const pi rc) {
    const vector<pi> ds{{-1, 0}, {-1, 1}, {0, 1},  {1, 1},
                        {1, 0},  {1, -1}, {0, -1}, {-1, -1}};
    vector<pi> ans(ds.size());
    transform(cbegin(ds), cend(ds), begin(ans),
              [rc](const pi d) { return rc + d; });
    return ans;
}

int count_neighs(const vector<string> &rows, const pi rc) {
    const auto [ro, co] = rc;
    int ans = 0;
    for (const auto neigh : neighs({ro, co})) {
        if (get_v(rows, neigh) == '#') ++ans;
    }
    return ans;
}

pair<bool, vector<string>> evolve(const vector<string> &rows) {
    const int H = rows.size();
    const int W = rows[0].size();

    vector<string> ans(rows);
    bool changed = false;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            const char v = rows[ro][co];
            if (v == '.') continue;

            const int nc = count_neighs(rows, {ro, co});

            if (v == 'L') {
                if (!nc) {
                    ans[ro][co] = '#';
                    changed = true;
                }
            } else {
                assert(v == '#');
                if (nc >= 4) {
                    ans[ro][co] = 'L';
                    changed = true;
                }
            }
        }
    }

    return {changed, ans};
}

int fixpoint_occupied_seats_count(vector<string> &rows) {
    for (;;) {
        bool changed = false;
        tie(changed, rows) = evolve(rows);
        if (!changed) break;
    }

    const auto occ_count = [](const string &s) -> int {
        return count(cbegin(s), cend(s), '#');
    };

    return ttransform_reduce(cbegin(rows), cend(rows), 0, plus{}, occ_count);
}

int main() {
    vector<string> rows;

    for (string line; getline(cin, line);) {
        rows.push_back(line);
    }

    cout << fixpoint_occupied_seats_count(rows) << '\n';
    return 0;
}
