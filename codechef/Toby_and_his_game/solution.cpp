#include <bits/stdc++.h>
using namespace std;

map<char, int> gather_counts(const string &s) {
    map<char, int> ans{{'U', 0}, {'D', 0}, {'L', 0}, {'R', 0}};
    for (const char d : s) ++ans[d];
    return ans;
}

int max_score(const string &s) {
    const auto cs = gather_counts(s);
    int ans = 0;
    ans += min(cs.at('L'), cs.at('R')) * 2;
    ans += min(cs.at('U'), cs.at('D')) * 2;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string s(n, ' ');
        cin >> s;

        cout << max_score(s) << '\n';
    }

    return 0;
}
