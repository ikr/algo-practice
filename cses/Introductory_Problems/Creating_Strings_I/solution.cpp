#include <bits/stdc++.h>
using namespace std;

int factorial(const int n) { return n < 3 ? n : n * factorial(n - 1); }

vector<int> gather_counts(const string &s) {
    vector<int> ans('z' - 'a' + 1, 0);
    for (const char c : s) ++ans[c - 'a'];
    return ans;
}

int count_permutations(const string &s) {
    int ans = factorial(s.size());
    for (const int x : gather_counts(s)) {
        if (x < 2) continue;
        ans /= factorial(x);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;
    sort(s.begin(), s.end());

    cout << count_permutations(s) << '\n';
    do {
        cout << s << '\n';
    } while (next_permutation(s.begin(), s.end()));

    return 0;
}
