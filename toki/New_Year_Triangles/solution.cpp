#include <bits/stdc++.h>
using namespace std;

int min_sides(int n) {
    if (n == 1) return 3;
    if (n == 2) return 4;
    return n % 2 ? 4 : 3;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    cout << min_sides(n) << '\n';

    return 0;
}
