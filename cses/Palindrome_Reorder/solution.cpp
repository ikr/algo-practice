#include <bits/stdc++.h>
using namespace std;

vector<int> count_chars(const string &s) {
    vector<int> ans('Z' - 'A' + 1, 0);
    for (const char c : s) ++ans[c - 'A'];
    return ans;
}

string palindromize(const string &s) {
    const auto cnt = count_chars(s);
    if (count_if(cnt.cbegin(), cnt.cend(), [](const int x) { return x % 2; }) >
        1) {
        return "NO SOLUTION";
    }

    const int sz = 'Z' - 'A' + 1;
    string ans;
    for (char c = 0; c != sz; ++c) {
        if (!cnt[c]) continue;

        if (cnt[c] % 2) {
            ans.insert(ans.size() / 2, string(cnt[c], 'A' + c));
        } else {
            const string appendix(cnt[c] / 2, 'A' + c);
            ans.insert(0, appendix);
            ans.append(appendix);
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;
    cout << palindromize(s) << '\n';

    return 0;
}
