#include <bits/stdc++.h>

using namespace std;

using Col = int;
using OptColRange = optional<pair<Col, Col>>;
using Row = int;
using Steps = unsigned long long;

Steps compute(const vector<OptColRange> &treasure_cols_by_row, const int k,
              const unordered_set<Col> &exit_columns) {

    return 0;
}

int main() {
    int n; // Rows
    int m; // Columns
    int k; // Treasures
    int q; // Safe columns
    cin >> n >> m >> k >> q;

    vector<set<Col>> treasure_column_sets_by_row(n);
    for (int i = 0; i != k; ++i) {
        int r1;
        int c1;
        cin >> r1 >> c1;
        treasure_column_sets_by_row[r1 - 1].insert(c1 - 1);
    }

    vector<OptColRange> treasure_cols_by_row(n);
    transform(treasure_column_sets_by_row.cbegin(),
              treasure_column_sets_by_row.cend(), treasure_cols_by_row.begin(),
              [](const set<Col> &cols_set) -> OptColRange {
                  if (cols_set.empty()) return nullopt;
                  return make_pair(*cols_set.cbegin(), *cols_set.crbegin());
              });

    unordered_set<Col> exit_columns;
    for (int i = 0; i != q; ++i) {
        int c1;
        cin >> c1;
        exit_columns.insert(c1 - 1);
    }

    cout << compute(treasure_cols_by_row, k, exit_columns) << '\n';
}
