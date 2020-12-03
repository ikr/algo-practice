#include <bits/stdc++.h>
using namespace std;

int count_trees_along_vector_1_3(const vector<string> &rows) {
    const int H = rows.size();
    const int W = rows[0].size();

    int ans = 0;

    for (int r = 0, c = 0; r < H; ++r, c += 3) {
        if (rows[r][c % W] == '#') ++ans;
    }

    return ans;
}

int main() {
    vector<string> rows;
    for (string row; getline(cin, row);) {
        rows.push_back(row);
    }

    cout << count_trees_along_vector_1_3(rows) << '\n';
    return 0;
}
