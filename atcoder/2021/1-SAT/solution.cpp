#include <bits/stdc++.h>
using namespace std;

string solve(const vector<string> &ss) {
    set<string> prefixed;
    set<string> unprefixed;

    for (const auto &s : ss) {
        if (s[0] == '!') {
            prefixed.insert(s.substr(1));
        } else {
            unprefixed.insert(s);
        }
    }

    for (const auto &s : unprefixed) {
        if (prefixed.count(s)) return s;
    }

    return "satisfiable";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<string> ss(n);
    for (auto &s : ss) {
        cin >> s;
    }

    cout << solve(ss) << '\n';
    return 0;
}
