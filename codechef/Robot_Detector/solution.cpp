#include <bits/stdc++.h>
using namespace std;

string moves(const int R, const int C) {
    string ans{"U"};

    for (int y = 1; y <= R; ++y) {
        ans += string(C * y, y % 2 ? 'R' : 'L');
        if (y != R) ans += 'U';
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int R, C;
    cin >> R >> C;
    cout << moves(R, C) << '\n';

    return 0;
}
