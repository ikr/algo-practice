#include <bits/stdc++.h>
using namespace std;

constexpr int SZ = 'z' - 'a' + 1;

string solve(const string &s) {
    const int sz = s.size();
    vector<int> best(SZ, -1);

    for (int i = 0; i < sz; ++i) {
        if (best[s[i] - 'a'] == -1) {
            best[s[i] - 'a'] = i;
        }
    }

    string ans;
    int last = INT_MIN;

    for (int i = SZ - 1; i >= 0; --i) {
        if (best[i] == -1) continue;

        if (best[i] > last) {
            ans += static_cast<char>('a' + i);
            last = best[i];
        }
    }

    return ans;
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

        cout << solve(s) << '\n';
    }

    return 0;
}
