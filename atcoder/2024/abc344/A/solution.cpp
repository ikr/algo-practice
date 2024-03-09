#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s;
    cin >> s;

    const auto i1 = s.find('|');
    const auto i2 = s.find('|', i1 + 1);

    const auto ans = s.substr(0, i1) + s.substr(i2 + 1);
    cout << ans << '\n';
    return 0;
}
