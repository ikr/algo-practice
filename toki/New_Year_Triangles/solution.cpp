#include <bits/stdc++.h>
using namespace std;

int min_sides(int n) {
    while (n >= 4) n = n / 4 + n % 4;
    assert(n > 0);
    assert(n < 4);

    return n == 1 ? 3 : 4;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    cout << min_sides(n) << '\n';

    return 0;
}
