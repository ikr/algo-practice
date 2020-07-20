#include <bits/stdc++.h>
using namespace std;

vector<int> gather_balanced_ranges_rights_by_left(const string &s) {
    const int sz = s.size();
    stack<int> st;
    vector<int> ans(sz, -2);

    for (int i = 0; i < sz; ++i) {
        if (s[i] == '(') {
            st.push(i);
        } else if (!st.empty()) {
            assert(s[i] == ')');
            ans[st.top()] = i;
            st.pop();
        }
    }

    return ans;
}

vector<int> min_counter_attack_indices(const string &brackets,
                                       const vector<int> &xs) {
    auto goods = gather_balanced_ranges_rights_by_left(brackets);
    const int sz = brackets.size();
    for (int i = sz - 1, closest_good = INT_MAX, closest_bad = INT_MAX; i >= 0;
         --i) {
        if (brackets[i] == '(') {
            if (goods[i] >= 0) {
                closest_good = i;
            } else {
                closest_bad = i;
            }
        }

        if (closest_good < closest_bad) {
            goods[i] = goods[closest_good];
        }
    }

    vector<int> ans(xs.size(), -2);
    transform(xs.cbegin(), xs.cend(), ans.begin(),
              [&goods](const int x) { return goods[x]; });
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
        vector<int> xs(sz, 0);

        for (auto &x : xs) {
            cin >> x;
            --x;
        }

        for (const auto x : min_counter_attack_indices(s, xs)) {
            cout << (x + 1) << '\n';
        }
    }

    return 0;
}
