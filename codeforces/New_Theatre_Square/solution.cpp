#include <bits/stdc++.h>
#include <numeric>
using namespace std;
using vs = vector<string>;
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

int count_whites(const vs &rows) {
    return accumulate(rows.cbegin(), rows.cend(), 0,
                      [](const int agg, const auto &row) {
                          return agg + count(row.cbegin(), row.cend(), '.');
                      });
}

pi min_pieces(const string &row) {
    const int sz = row.size();
    pi ans{0, 0};

    for (int i = 0; i < sz; ++i) {
        if (row[i] == '*') continue;

        if (i != sz - 1 && row[i + 1] == '.') {
            ++ans.second;
            ++i;
        } else {
            ++ans.first;
        }
    }

    return ans;
}

int min_costs(const vs &rows, const int price1, const int price2) {
    if (price1 * 2 <= price2) return count_whites(rows) * price1;

    const auto [ones, twos] = ttransform_reduce(
        rows.cbegin(), rows.cend(), pi{0, 0},
        [](const pi &agg, const pi pcs) { return agg + pcs; }, min_pieces);

    return ones * price1 + twos * price2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m, x, y;
        cin >> n >> m >> x >> y;
        vs rows(n, "");
        for (auto &row : rows) {
            cin >> row;
        }

        cout << min_costs(rows, x, y) << '\n';
    }

    return 0;
}
