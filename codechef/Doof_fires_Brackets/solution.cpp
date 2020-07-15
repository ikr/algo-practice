#include <bits/stdc++.h>
using namespace std;

pair<unordered_set<int>, set<pair<int, int>>> balanced_ranges(const string &s) {
    const int sz = s.size();
    stack<int> st;
    unordered_set<int> ans1;
    set<pair<int, int>> ans2;

    for (int i = 0; i < sz; ++i) {
        if (s[i] == '(') {
            st.push(i);
        } else if (!st.empty()) {
            assert(s[i] == ')');
            ans1.insert(st.top());
            ans2.insert({st.top(), i});
            st.pop();
        }
    }

    return {ans1, ans2};
}

set<int> gather_bads(const string &s, const unordered_set<int> &good_lefts) {
    const int sz = s.size();
    set<int> ans;

    for (int i = 0; i < sz; ++i) {
        if (s[i] == ')') continue;
        if (!good_lefts.count(i)) ans.insert(i);
    }

    return ans;
}

vector<int> min_counter_attack_indices(const string &brackets,
                                       const vector<int> &xs) {
    const auto [good_lefts, goods] = balanced_ranges(brackets);
    const auto bads = gather_bads(brackets, good_lefts);

    const int qs = xs.size();
    vector<int> ans(qs, -2);

    for (int i = 0; i < qs; ++i) {
        const auto git = goods.lower_bound(pair<int, int>{xs[i], -1});

        if (git == goods.cend()) {
            ans[i] = -2;
        } else {
            const auto bit = bads.lower_bound(xs[i]);
            const int bi = bit == bads.cend() ? INT_MAX : *bit;

            ans[i] = bi < git->first ? -2 : git->second;
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

        cout << flush;
    }

    return 0;
}
