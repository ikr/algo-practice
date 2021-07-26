#include <bits/stdc++.h>
using namespace std;

int food_code(const int a, const int b) {
    const int ms = a + b;
    const int mf = ms - a;

    if (ms >= 15 && mf >= 8) return 1;
    if (ms >= 10 && mf >= 3) return 2;
    if (ms >= 3) return 3;
    return 4;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int a, b;
    cin >> a >> b;
    cout << food_code(a, b) << '\n';

    return 0;
}
