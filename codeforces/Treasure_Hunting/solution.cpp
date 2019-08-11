#include <bits/stdc++.h>

using namespace std;

using Col = int;
using StepsCol = pair<int, Col>;

StepsCol move_to_closest(const StepsCol current, const set<Col> &dest) {
    const auto [steps, col] = current;
    if (dest.empty() || dest.count(col)) return current;

    const auto it = upper_bound(cbegin(dest), cend(dest), col);
    if (it == cbegin(dest)) return {abs(col - *cbegin(dest)), *cbegin(dest)};
    if (it == cend(dest)) return {abs(col - *crbegin(dest)), *crbegin(dest)};

    const Col a = *prev(it);
    const Col b = *it;

    return min(make_pair(abs(a - col), a), make_pair(abs(b - col), b));
}

int main() {
    int n;
    int m;
    int k;
    int q;
    cin >> n >> m >> k >> q;

    vector<set<Col>> treasure_column_sets_by_row(n);
    for (int i = 0; i != k; ++i) {
        int r1;
        int c1;
        cin >> r1 >> c1;
        treasure_column_sets_by_row[r1 - 1].insert(c1 - 1);
    }

    set<Col> exit_columns;
    for (int i = 0; i != q; ++i) {
        int c1;
        cin >> c1;
        exit_columns.insert(c1 - 1);
    }
}
