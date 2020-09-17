#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const unordered_set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

int max_occurances_one_letter(const int k, const string &s, const char l) {
    const int n = s.size();
    const int ls = count(cbegin(s), cend(s), l);
    const int not_ls = n - ls;
    const int d = min(k, not_ls);

    return (ls + d) * (ls + d - 1) / 2;
}

vi gather_freq_of(const char needle, const string &haystack) {
    const int n = haystack.size();
    vi ans(n, 0);
    for (int i = 1; i < n; ++i) {
        ans[i] = ans[i - 1];
        if (haystack[i - 1] == needle) ++ans[i];
    }
    return ans;
}

int max_occurances(const int k, const string &s, const char a, const char b) {
    if (a == b) return max_occurances_one_letter(k, s, a);
    const int n = s.size();
    const auto a_freq = gather_freq_of(a, s);

    // Maximum number of occurances [up to index p] after [r replacements used]
    vvi dp(n, vi(k + 1, 0));

    for (int p = 1; p < n; ++p) {
        dp[p][0] = dp[p - 1][0];
        if (s[p] == b) dp[p][0] += a_freq[p];

        for (int r = 1; r <= k; ++r) {
        }
    }

    cout << dp << '\n';

    return *max_element(cbegin(dp.back()), cend(dp.back()));
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
