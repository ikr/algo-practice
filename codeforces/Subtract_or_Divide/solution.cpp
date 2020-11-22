#include <bits/stdc++.h>
using namespace std;

int moves(const int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;
    if (n < 5) return 2;
    return n % 2 + 2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t{0};
    cin >> t;
    while (t--) {
        int n{0};
        cin >> n;
        cout << moves(n) << '\n';
    }

    return 0;
}
