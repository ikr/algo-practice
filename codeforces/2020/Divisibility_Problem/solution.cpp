#include <bits/stdc++.h>

using namespace std;

int count_moves(const int a, const int b) {
    if (a % b == 0) return 0;
    return b - a % b;
}

int main() {
    int t;
    cin >> t;

    for (int i = 0; i != t; ++i) {
        int a, b;
        cin >> a >> b;
        cout << count_moves(a, b) << '\n';
    }

    return 0;
}
