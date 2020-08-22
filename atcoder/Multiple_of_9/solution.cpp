#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    int nsum = 0;

    for (const auto d : s) {
        const int x = d - '0';
        nsum += x;
        nsum %= 9;
    }

    cout << (nsum == 0 ? "Yes" : "No") << '\n';

    return 0;
}
