#include <bits/stdc++.h>
using namespace std;

unordered_map<int, int> gather_balanced_ranges_rights_by_left(const string &s) {
    const int sz = s.size();
    stack<int> st;
    unordered_map<int, int> ans;

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

unordered_multimap<int, int> gather_indices_by_x(const vector<int> &xs) {
    const int sz = xs.size();
    unordered_multimap<int, int> ans;
    for (int i = 0; i != sz; ++i) {
        ans.emplace(xs[i], i);
    }
    return ans;
}

vector<int> min_counter_attack_indices(const string &brackets,
                                       const vector<int> &xs) {
    const auto goods = gather_balanced_ranges_rights_by_left(brackets);
    const auto idx = gather_indices_by_x(xs);

    const int qs = xs.size();
    vector<int> ans(qs, -2);

    const int sz = brackets.size();
    for (int i = sz - 1, closest_good = INT_MAX, closest_bad = INT_MAX; i >= 0;
         --i) {
        if (brackets[i] == '(') {
            if (goods.count(i)) {
                closest_good = i;
            } else {
                closest_bad = i;
            }
        }

        if (!idx.count(i)) continue;

        const auto [first, last] = idx.equal_range(i);
        for (auto j = first; j != last; ++j) {
            if (closest_good < closest_bad) {
                ans[j->second] = goods.at(closest_good);
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
