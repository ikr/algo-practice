#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pair<int, int>> run_length_encode(const vector<int> &xs) {
    vector<pair<int, int>> ans{{xs[0], 1}};
    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] == ans.back().first) {
            ++(ans.back().second);
        } else {
            ans.emplace_back(xs[i], 1);
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        string s;
        cin >> s;
        assert(sz(s) == n);

        vector<int> ind(m);
        for (auto &i : ind) {
            cin >> i;
            --i;
        };
        sort(begin(ind), end(ind));
        const auto rle = run_length_encode(ind);

        string c;
        cin >> c;
        assert(sz(c) == m);

        deque<char> dq(cbegin(c), cend(c));
        sort(begin(dq), end(dq));

        for (const auto &[i, f] : rle) {
            for (int j = 1; j < f; ++j) dq.pop_back();
            s[i] = dq.front();
            dq.pop_front();
        }

        cout << s << '\n';
    }

    return 0;
}
