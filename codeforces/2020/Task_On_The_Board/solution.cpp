#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

vi indices_of_zeros(const vi &bs) {
    const int sz = bs.size();
    vi ans;
    for (int i = 0; i != sz; ++i) {
        if (!bs[i]) ans.push_back(i);
    }
    return ans;
}

string construct_t(string s, vi bs) {
    const int sz = bs.size();
    map<char, int> counts;
    for (const auto c : s) {
        ++counts[c];
    }

    string ans(sz, '.');

    for (auto it = counts.crbegin(); it != counts.crend(); ++it) {
        const auto iz = indices_of_zeros(bs);
        if (iz.size() > it->second) continue;

        for (auto i : iz) {
            ans[i] = it->first;
            bs[i] = -1;
        }

        for (int i = 0; i != sz; ++i) {
            for (auto j : iz) {
                if (bs[i] > 0) {
                    bs[i] -= abs(i - j);
                }
            }
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
        string s;
        cin >> s;

        int sz;
        cin >> sz;
        vi bs(sz, 0);
        for (auto &b : bs) cin >> b;
        cout << construct_t(s, bs) << '\n';
    }

    return 0;
}
