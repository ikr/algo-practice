#include <bits/stdc++.h>
using namespace std;

int replacements(string s) {
    const int n = s.size();
    vector<bool> intact(n, true);

    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i - 1] && intact[i - 1]) {
            intact[i] = false;
        }

        if (i > 1 && s[i] == s[i - 2] && intact[i - 2]) {
            intact[i] = false;
        }
    }

    return count(cbegin(intact), cend(intact), false);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;

        cout << replacements(s) << '\n';
    }

    return 0;
}
