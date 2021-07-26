#include <bits/stdc++.h>
using namespace std;

int solve(const int x) {
    return 100 - (x % 100);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int x;
    cin >> x;

    cout << solve(x) << '\n';

    return 0;
}
