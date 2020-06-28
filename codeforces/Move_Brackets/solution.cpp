#include <bits/stdc++.h>
using namespace std;

int ops(const string &s) {
    int balance = 0;
    int ans = 0;

    for (const auto c : s) {
        if (c == '(')
            ++balance;
        else
            --balance;

        ans = min(ans, balance);
    }

    balance = 0;
    for (auto it = s.crbegin(); it != s.crend(); ++it) {
        const int c = *it;
        if (c == ')')
            ++balance;
        else
            --balance;

        ans = min(ans, balance);
    }

    return abs(ans);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int sz;
        cin >> sz;
        string s(sz, ' ');
        cin >> s;

        cout << ops(s) << '\n';
    }

    return 0;
}
