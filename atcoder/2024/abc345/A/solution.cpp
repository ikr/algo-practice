#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s;
    cin >> s;

    auto yes = s[0] == '<' && s.back() == '>';
    for (int i = 1; i < ssize(s) - 1; ++i) {
        if (s[i] != '=') yes = false;
    }
    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
