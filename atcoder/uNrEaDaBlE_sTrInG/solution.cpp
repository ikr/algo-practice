#include <bits/stdc++.h>
using namespace std;

bool is_up(const char c) { return 'A' <= c && c <= 'Z'; }
bool is_lo(const char c) { return 'a' <= c && c <= 'z'; }

bool is_hard(const string &s) {
    const int n = s.size();
    for (int i = 0; i < n; ++i) {
        const int pos = i + 1;
        if (pos % 2) {
            if (!is_lo(s[i])) return false;
        } else {
            if (!is_up(s[i])) return false;
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;
    cout << (is_hard(s) ? "Yes" : "No") << '\n';

    return 0;
}
