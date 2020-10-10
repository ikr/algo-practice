#include <bits/stdc++.h>
#include <cctype>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    char s, t;
    cin >> s >> t;

    const char ans = (s == 'Y' ? toupper(t) : t);
    cout << ans << '\n';

    return 0;
}
