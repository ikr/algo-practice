#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    string s;
    cin >> s;

    s.erase(unique(begin(s), end(s)), end(s));
    cout << s << '\n';

    return 0;
}
