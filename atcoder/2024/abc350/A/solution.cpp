#include <bits/stdc++.h>
using namespace std;

bool is_abc(const string &s) {
    const auto n = stoi(s.substr(3));
    if (n == 316) return false;
    return 0 < n && n < 350;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s;
    cin >> s;

    cout << (is_abc(s) ? "Yes" : "No") << '\n';

    return 0;
}
