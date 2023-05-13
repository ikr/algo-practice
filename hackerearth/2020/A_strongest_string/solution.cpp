#include <bits/stdc++.h>
using namespace std;

constexpr int AZ = 'z' - 'a' + 1;

vector<set<int>> gather_char_indices(const string &s) {
    const int sz = s.size();
    vector<set<int>> ans(AZ);

    for (int i = 0; i < sz; ++i) {
        ans[s[i] - 'a'].insert(i);
    }

    return ans;
}

string solve(const string &s) {
    string ans;
    vector<bool> used(AZ, false);
    const auto indices_by_char = gather_char_indices(s);

    for (int last_index = -1;;) {
        bool appended = false;

        for (auto cit = indices_by_char.crbegin();
             cit != indices_by_char.crend(); ++cit) {
            const char c = 'z' - distance(indices_by_char.crbegin(), cit);
            if (used[c - 'a']) continue;

            const auto iit = cit->upper_bound(last_index);
            if (iit == cit->cend()) continue;

            ans += c;
            used[c - 'a'] = true;
            last_index = *iit;
            appended = true;
            break;
        }

        if (!appended) break;
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
