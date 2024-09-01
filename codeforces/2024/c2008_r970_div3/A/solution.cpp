#include <bits/stdc++.h>
using namespace std;

bool is_possible(const int a, const int b) {
    if (a % 2 == 0 && b % 2 == 0) return true;

    if (a % 2 == 0 && b % 2) {
        return a >= 2;
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << (is_possible(a, b) ? "YES" : "NO") << '\n';
    }

    return 0;
}
