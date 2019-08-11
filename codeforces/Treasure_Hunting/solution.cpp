#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    int m;
    int k;
    int q;
    cin >> n >> m >> k >> q;

    vector<set<int>> treasure_column_sets_by_row(n);
    for (int i = 0; i != k; ++i) {
        int r1;
        int c1;
        cin >> r1 >> c1;
        treasure_column_sets_by_row[r1 - 1].insert(c1 - 1);
    }

    set<int> exit_columns;
    for (int i = 0; i != q; ++i) {
        int c1;
        cin >> c1;
        exit_columns.insert(c1 - 1);
    }
}
