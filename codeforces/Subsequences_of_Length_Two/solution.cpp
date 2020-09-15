#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

int max_occurances_one_letter(const int k, const string &s, const char l) {
    const int n = s.size();
    const int ls = count(cbegin(s), cend(s), l);
    const int not_ls = n - ls;
    const int d = min(k, not_ls);

    return (ls + d) * (ls + d - 1) / 2;
}

int max_occurances(const int k, const string &s, const char a, const char b) {
    if (a == b) return max_occurances_one_letter(k, s, a);
    const int n = s.size();

    // The value is -1 if the indices combination is impossible. Otherwise, it's
    // the maximum number of occurances
    // [up to index p] with [q letters a] after [r replacements used]
    vector<vvi> dp(n, vvi(n + 1, vi(k + 1, -1)));
    if (s[0] == a) {
        dp[0][0][1] = 0;
        dp[0][1][0] = 0;
    } else {
        dp[0][0][0] = 0;
        dp[0][1][1] = 0;
    }

    for (int r = 0; r < n; ++r) {
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    string s(n, ' ');
    cin >> s;

    string t;
    cin >> t;

    cout << max_occurances(k, s, t[0], t[1]) << '\n';
    return 0;
}
