#include <bits/stdc++.h>
using namespace std;

int kyu(const int x) {
    if (x >= 1800) return 1;
    if (x >= 1600) return 2;
    if (x >= 1400) return 3;
    if (x >= 1200) return 4;
    if (x >= 1000) return 5;
    if (x >= 800) return 6;
    if (x >= 600) return 7;
    if (x >= 400) return 8;
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    cout << kyu(t) << '\n';

    return 0;
}
