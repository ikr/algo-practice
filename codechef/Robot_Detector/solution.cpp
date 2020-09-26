#include <bits/stdc++.h>
using namespace std;

string moves(const int R, const int C) {
    string ans(C - 1, 'R');
    ans.insert(cbegin(ans), 'U');
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
