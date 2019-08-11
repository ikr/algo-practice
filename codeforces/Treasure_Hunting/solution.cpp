#include <bits/stdc++.h>

using namespace std;

using Col = int;
using Row = int;
using Steps = unsigned long long;
using StepsCol = pair<Steps, Col>;

StepsCol move_to_closest(const StepsCol current, const set<Col> &dest) {
    const auto [steps, col] = current;
    if (dest.empty() || dest.count(col)) return current;

    const auto it = upper_bound(cbegin(dest), cend(dest), col);
    if (it == cbegin(dest))
        return {steps + abs(col - *cbegin(dest)), *cbegin(dest)};
    if (it == cend(dest))
        return {steps + abs(col - *crbegin(dest)), *crbegin(dest)};

    const Col a = *prev(it);
    const Col b = *it;

    return min(make_pair(steps + abs(a - col), a),
               make_pair(steps + abs(b - col), b));
}

StepsCol run_level(const StepsCol current, const set<Col> &treasures,
                   const set<Col> &exits) {
    if (treasures.empty()) return move_to_closest(current, exits);
    const auto [steps, entrance] = current;

    if (*crbegin(treasures) <= entrance || entrance <= *cbegin(treasures))
        return *crbegin(treasures) <= entrance
                   ? move_to_closest({steps + entrance - *cbegin(treasures),
                                      *cbegin(treasures)},
                                     exits)
                   : move_to_closest({steps + *crbegin(treasures) - entrance,
                                      *crbegin(treasures)},
                                     exits);

    const auto treasure_spread = *crbegin(treasures) - *cbegin(treasures);

    const Steps steps_a =
        steps + entrance - *cbegin(treasures) + treasure_spread;
    const Col col_a = *crbegin(treasures);

    const Steps steps_b =
        steps + *crbegin(treasures) - entrance + treasure_spread;
    const Col col_b = *cbegin(treasures);

    return min(move_to_closest({steps_a, col_a}, exits),
               move_to_closest({steps_b, col_b}, exits));
}

Steps compute(const vector<set<Col>> &treasure_column_sets_by_row,
              const int treasures_count, const set<Col> &exit_columns) {
    StepsCol current{0, 0};
    Row row = 0;
    int collected = 0;

    while (collected != treasures_count) {
        const bool last_level =
            static_cast<int>(treasure_column_sets_by_row[row].size()) ==
            (treasures_count - collected);

        current = run_level(current, treasure_column_sets_by_row[row],
                            last_level ? set<Col>{} : exit_columns);
        if (!last_level) ++current.first;

        collected += treasure_column_sets_by_row[row].size();
        ++row;
    }

    return current.first;
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

    cout << compute(treasure_column_sets_by_row, k,
                    static_cast<int>(exit_columns.size()) == m ? set<Col>{}
                                                               : exit_columns)
         << '\n';
}
