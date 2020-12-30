#include <bits/stdc++.h>
using namespace std;

char next_char(const char x) {
    const int m = 'z' - 'a' + 1;
    return (((x - 'a') + 1) % m) + 'a';
}

char suggest(const set<char> &neighs) {
    const char x = *max_element(cbegin(neighs), cend(neighs));
    return next_char(x);
}

int replacements(string s) {
    const int n = s.size();
    int ans = 0;

    for (int i = 1; i < n; ++i) {
        const char l3 = i >= 3 ? s[i - 3] : s[i];
        const char l2 = i >= 2 ? s[i - 2] : s[i];
        const char l1 = i >= 1 ? s[i - 1] : s[i];

        const char r1 = i < n - 1 ? s[i + 1] : s[i];
        const char r2 = i < n - 2 ? s[i + 2] : s[i];

        if (i < n - 1) {
            if (s[i - 1] == s[i] && s[i] == s[i + 1]) { // a a a
                s[i - 1] = suggest({l3, l2, l1});
                s[i] = suggest({l2, l1, s[i - 1], r2});
                ++ans;
                continue;
            } else if (s[i - 1] == s[i + 1]) { // a b a
                s[i - 1] = suggest({l3, l2, l1, s[i]});
                ++ans;
                continue;
            }
        }

        if (s[i - 1] == s[i]) {
            s[i - 1] = suggest({l3, l2, l1, r1});
            ++ans;
        }
    }

    cout << s << '\n';
    return ans;
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
