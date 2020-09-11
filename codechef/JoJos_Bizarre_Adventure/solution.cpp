#include <bits/stdc++.h>
using namespace std;
constexpr int SZ = 'z' - 'a' + 1;

vector<bool> chars_in(const string &s) {
    vector<bool> ans(SZ, false);
    for (const char c : s) ans[c - 'a'] = true;
    return ans;
}

vector<int> gather_counts(const string &s) {
    vector<int> ans(SZ, 0);
    for (const char c : s) ++ans[c - 'a'];
    return ans;
}

bool a_contains_b(const vector<int> &a, const vector<bool> &b) {
    for (int i = 0; i < SZ; ++i) {
        if (b[i] && !a[i]) return false;
    }

    return true;
}

string char_num(const char c) {
    const int x = c - 'a' + 1;
    return to_string(x);
}

string digest(const string &s) {
    const int n = s.size();
    const auto full = chars_in(s);
    vector<int> curr(SZ, 1);
    int lo = -1;
    int hi = -1;
    pair<int, int> best{0, 1e7};

    while (lo < n && hi < n) {
        if (a_contains_b(curr, full)) {
            if (lo >= 0 && best.second - best.first > hi - lo) {
                best = {lo, hi};
            }

            vector<int> cc = curr;
            if (lo >= 0) --cc[s[lo] - 'a'];
            if (lo >= 0 && a_contains_b(cc, full)) {
                ++lo;
                curr = cc;
            } else {
                ++lo;
                hi = lo;

                if (lo < n) {
                    fill(begin(curr), end(curr), 0);
                    curr[s[lo] - 'a'] = 1;
                }
            }
        } else {
            ++hi;
            if (hi < n) {
                ++curr[s[hi] - 'a'];
            }
        }
    }

    string ans;
    for (int i = best.first; i <= best.second; ++i) {
        ans += char_num(s[i]);
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
        cout << digest(s) << '\n';
    }

    return 0;
}
