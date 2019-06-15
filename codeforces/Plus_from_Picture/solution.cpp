#include <bits/stdc++.h>

using namespace std;

int main() {
    int rows_count;
    int cols_count;
    cin >> rows_count >> cols_count;

    vector<string> rows;

    for (int i = 0; i != rows_count; ++i) {
        string row;
        cin >> row;
        rows.push_back(row);
    }

    cout << '\n';
    for (const auto row : rows) {
        cout << row << '\n';
    }
}
