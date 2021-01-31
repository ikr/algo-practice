#include <bits/stdc++.h>
using namespace std;

vector<string> print_raster(const int s, const int n) {
    return {"- - -", "| | |"};
}

int main() {
    for (int i = 0;; ++i) {
        int s, n;
        cin >> s >> n;
        if (!s) break;

        if (i) cout << '\n';

        const auto rows = print_raster(s, n);
        for (const auto &row : rows) cout << row << '\n';
    }
    return 0;
}
