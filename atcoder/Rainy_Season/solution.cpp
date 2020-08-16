#include <bits/stdc++.h>
using namespace std;

int max_rainy(const string &s) {
    if (s.empty()) return 0;
    const int sz = s.size();

    int curr = s[0] == 'R' ? 1 : 0;
    int ans = curr;

    for (int i = 1; i < sz; ++i) {
        if (s[i] == 'R') {
            if (s[i - 1] == 'R') {
                ++curr;
            } else {
                curr = 1;
            }
        } else {
            ans = max(curr, ans);
            curr = 0;
        }
    }

    ans = max(ans, curr);

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    cout << max_rainy(s) << '\n';

    return 0;
}
