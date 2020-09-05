#include <bits/stdc++.h>
using namespace std;

vector<string> color(const int H, const int W) {
    string row(W, 'W');
    for (int co = 0; co < W; ++co) {
        if (co % 2) row[co] = 'B';
    }

    return vector<string>(H, row);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int H, W;
    cin >> H >> W;

    for (const auto &row : color(H, W)) {
        cout << row << '\n';
    }

    return 0;
}
