#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int a, b, s;
    cin >> a >> b >> s;

    const int d = abs(a) + abs(b);
    bool ans = (s >= d) && (s - d) % 2 == 0;

    cout << (ans ? "Yes" : "No") << '\n';
    return 0;
}
