#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int a, b;
    cin >> a >> b;
    const string s = to_string(a + b);
    cout << s.length() << '\n';

    return 0;
}
